#ifndef INCLUDE_SO_UNICODE_ERROR_ONCE_FLAG
#define INCLUDE_SO_UNICODE_ERROR_ONCE_FLAG

#include <stdexcept>

namespace so {
    class utf8_byte_error :
      public std::domain_error
    {
    public:
        utf8_byte_error(char byte, bool start) :
          std::domain_error(std::to_string(byte) + " is not a valid " + (start ? "start" : "trail") + " byte.") {
        }
    };

    class utf16_surrogate_error :
      public std::domain_error
    {
    public:
        utf16_surrogate_error(char16_t code, bool high) :
          std::domain_error(std::to_string(code) + " is not a valid " + (high ? "high" : "low") + " surrogate.") {
        }
    };

    class utf32_code_error :
      public std::domain_error
    {
    public:
        utf32_code_error(char32_t code) :
          std::domain_error(std::to_string(code) + " is not a valid code point.") {
        }
    };

    class unicode_escape_error :
      public std::domain_error
    {
    public:
        unicode_escape_error(const std::string& what) :
          std::domain_error(what) {
        }
    };
}

#endif//INCLUDE_SO_UNICODE_ERROR_ONCE_FLAG
