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

    class utf8_start_error :
      public std::domain_error
    {
    public:
        utf8_start_error(char byte) :
          std::domain_error(std::to_string(byte) + " is not a valid UTF-8 start byte.") {
        }
    };

    class utf8_trail_error :
      public std::domain_error
    {
    public:
        utf8_trail_error(char byte) :
          std::domain_error(std::to_string(byte) + " is not a valid UTF-8 trail byte.") {
        }
    };

    class utf16_high_error :
      public std::domain_error
    {
    public:
        utf16_high_error(char16_t surrogate) :
          std::domain_error(std::to_string(surrogate) + " is not a valid UTF-16 high surrogate.") {
        }
    };

    class utf16_low_error :
      public std::domain_error
    {
    public:
        utf16_low_error(char16_t surrogate) :
          std::domain_error(std::to_string(surrogate) + " is not a valid UTF-16 low surrogate.") {
        }
    };

    class utf32_code_error :
      public std::domain_error
    {
    public:
        utf32_code_error(char32_t code) :
          std::domain_error(std::to_string(code) + " is not a valid Unicode code point.") {
        }
    };
}

#endif//INCLUDE_SO_UNICODE_ONCE_FLAG
