#include "unicode.hpp"
#include "cast.hpp"

namespace so {
    std::u16string& operator+=(std::u16string& utf16, char32_t code) {
        if (code <= 0xFFFF) {
            utf16 += char16_t(code);
        }
        else if (code <= 0x10FFFF) {
            code -= 0x10000;
            utf16 += char16_t((code >> 10) + 0xD800);
            utf16 += char16_t(code & 0x03FF + 0xDC00);
        }
        else {
            throw unicode_cast_error{std::to_string(code) + " is not a valid code point."};
        }
        return utf16;
    }

    std::u16string utf16(const std::string& utf8) {
        return utf32_indirect<std::u16string, std::string>(utf8);
    }

    std::u16string utf16(const std::u32string& utf32) {
        return utf32_direct<std::u16string>(utf32);
    }

    std::u16string utf16(char32_t utf32) {
        return utf32_single<std::u16string>(utf32);
    }
}
