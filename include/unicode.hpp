#ifndef INCLUDE_SO_UNICODE_ONCE_FLAG
#define INCLUDE_SO_UNICODE_ONCE_FLAG

#include <string>
#include <stdexcept>

namespace so {
    std::string utf8(const std::string& mbcs, const char* encoding = "");

    std::string mbcs(const std::string& utf8, const char* encoding = "");

    std::string utf8(const std::u16string& utf16);

    std::string utf8(const std::u32string& utf32);

    std::string utf8(char32_t utf32);

    std::u16string utf16(const std::string& utf8);

    std::u16string utf16(const std::u32string& utf32);

    std::u16string utf16(char32_t utf32);

    std::u32string utf32(const std::string& utf8);

    std::u32string utf32(const std::u16string& utf16);

    using u8i_t = std::string::const_iterator;

    char32_t utf32(u8i_t& utf8);

    using u16i_t = std::u16string::const_iterator;

    char32_t utf32(u16i_t& utf16);

    std::string escape(const std::u16string& utf16);

    std::string escape(const std::u32string& utf32);

    char32_t escaped(u8i_t& literals);

    class unicode_cast_error :
      public std::domain_error
    {
    public:
        unicode_cast_error(const std::string& what) :
          std::domain_error(what) {
        }
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

#endif//INCLUDE_SO_UNICODE_ONCE_FLAG
