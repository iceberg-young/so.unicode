#include "unicode.hpp"
#include "cast.hpp"

namespace so {
    namespace {
        char32_t shift_in(unicode::u8i_t& iterator, int rest, char32_t code) {
            for (int i = 0; i < rest; ++i) {
                char trail = *iterator++;
                if (~(trail >> 6) != 1) { // 0b10xxxxxx
                    throw unicode_cast_error{
                      std::to_string(trail) + " is not a valid UTF-8 trail byte."
                    };
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

    char32_t utf32(unicode::u8i_t& utf8) {
        char32_t code = *utf8++;
        if (~code & 0b10000000) {
            // Single byte, nothing to do
        }
        else if (~(code >> 5) == 1) { //    0b110xxxxx
            code = shift_in(utf8, 1, code & 0b00011111);
        }
        else if (~(code >> 4) == 1) { //    0b1110xxxx
            code = shift_in(utf8, 2, code & 0b00001111);
        }
        else if (~(code >> 3) == 1) { //    0b11110xxx
            code = shift_in(utf8, 3, code & 0b00000111);
        }
        else {
            throw unicode_cast_error{
              std::to_string(code) + " is not a valid UTF-8 start byte."
            };
        }
        return code;
    }

    char32_t utf32(unicode::u16i_t& utf16) {
        char16_t code = *utf16++;
        return is::surrogate(code) ? utf32(code, *utf16++) : code;
    }
}
