#include "unicode.hpp"
#include "cast.hpp"

namespace so {
    namespace {
        char32_t shift_in(u8i_t& iterator, int rest, char32_t code) {
            for (int i = 0; i < rest; ++i) {
                char trail = *iterator++;
                if (trail | 0b11000000 != 0b10000000) {
                    throw utf8_trail_error{trail};
                }
                code <<= 6;
                code |= trail & 0b00111111;
            }
            return code;
        }
    }

    std::u32string utf32(const std::string& utf8) {
        return utf32_indirect<std::u32string, std::string>(utf8);
    }

    std::u32string utf32(const std::u16string& utf16) {
        return utf32_indirect<std::u32string, std::u16string>(utf16);
    }

    char32_t utf32(u8i_t & utf8) {
        char32_t code = *utf8++;
        if (!(code & 0b10000000)) {
            // Nothing to do
        }
        else if (!(code & 0b00100000)) { // 0b110xxxxx
            code = shift_in(utf8, 1, code & 0b00011111);
        }
        else if (!(code & 0b00010000)) { // 0b1110xxxx
            code = shift_in(utf8, 2, code & 0b00001111);
        }
        else if (!(code & 0b00001000)) { // 0b11110xxx
            code = shift_in(utf8, 3, code & 0b00000111);
        }
        else {
            throw utf8_start_error{char(code)};
        }
        return code;
    }

    char32_t utf32(u16i_t & utf16) {
        char32_t high = *utf16++;
        if (high < 0xD800 or high >= 0xE000) return high;
        if (high >= 0xDC00) {
            throw utf16_high_error{char16_t(high)};
        }
        char32_t low = *utf16++;
        if (low < 0xDC00 or low >= 0xE000) {
            throw utf16_low_error{char16_t(low)};
        }
        return 0x10000 + ((high - 0xD800) << 10) + (low - 0xDC00);
    }
}
