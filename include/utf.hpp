/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include <string>
#include <stdexcept>

namespace so {
    namespace utf {
        using u8i_t = std::string::const_iterator;

        using u16i_t = std::u16string::const_iterator;

        /**
         * Escaped forms. E.g. \u1234 or \U12345678
         */
        std::string escape(const std::u16string& utf16);

        std::string escape(const std::u32string& utf32);

        char32_t escaped(u8i_t& literals);
    }

    /**
     * Convert between UTF-8 and Multi-byte Character Set (MBCS).
     */
    std::string utf8(const std::string& mbcs, const char* encoding = "");

    std::string mbcs(const std::string& utf8, const char* encoding = "");

    /**
     * To UTF-8.
     */
    std::string utf8(const std::u16string& utf16);

    std::string utf8(const std::u32string& utf32);

    std::string utf8(char32_t utf32);

    std::string& operator+=(std::string& utf8, char32_t code);

    /**
     * To UTF-16.
     */
    std::u16string utf16(const std::string& utf8);

    std::u16string utf16(const std::u32string& utf32);

    std::u16string utf16(char32_t utf32);

    std::u16string& operator+=(std::u16string& utf16, char32_t code);

    /**
     * To UTF-32.
     */
    std::u32string utf32(const std::string& utf8);

    std::u32string utf32(const std::u16string& utf16);

    char32_t utf32(utf::u8i_t& utf8);

    char32_t utf32(utf::u16i_t& utf16);

    class unicode_cast_error :
      public std::domain_error {
     public:
        unicode_cast_error(const std::string& what) :
          domain_error(what) {}
    };

    namespace is {
        inline bool high_surrogate(char32_t code) {
            return code >= 0xD800 and code <= 0xDBFF;
        }

        inline bool low_surrogate(char32_t code) {
            return code >= 0xDC00 and code <= 0xDFFF;
        }

        inline bool surrogate(char32_t code) {
            return code >= 0xD800 and code <= 0xDFFF;
        }
    }
}
