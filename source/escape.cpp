#include <sstream>
#include "unicode.hpp"
#include "cast.hpp"

namespace so {
    namespace {
        template<typename in_t>
        std::string escape(const in_t& literals, const std::string& prefix, size_t width) {
            std::stringstream ss;
            ss.fill('0');
            ss << std::hex;
            for (auto c : literals) {
                ss << prefix;
                ss.width(width);
                ss << c;
            }
            return ss.str();
        }

        char32_t hex(u8i_t& literals, int amount) {
            char32_t value = 0;
            for (int i = 0; i < amount; ++i, ++literals) {
                value <<= 4;
                char quad = *literals;
                if (quad >= '0' and quad <= '9') {
                    value += quad - '0';
                }
                else if (quad >= 'A' and quad <= 'F') {
                    value += quad - 'A' + 10;
                }
                else if (quad >= 'a' and quad <= 'f') {
                    value += quad - 'a' + 10;
                }
                else {
                    throw unicode_escape_error{"Hexadigit (0-9, A-F, or a-f) is expected."};
                }
            }
            return value;
        }
    }

    std::string escape(const std::u16string& utf16) {
        return escape(utf16, "\\u", 4);
    }

    std::string escape(const std::u32string& utf32) {
        return escape(utf32, "\\U", 8);
    }

    char32_t escaped(u8i_t& literals) {
        if (*literals != '\\') {
            throw unicode_escape_error{"Back slash (\\) is expected."};
        }
        switch (*++literals) {
            case 'U': {
                return hex(++literals, 8);
            }
            case 'u': {
                char32_t code = hex(++literals, 4);
                if (is::high_surrogate(code)) {
                    code = utf32(code, escaped(literals));
                }
                return code;
            }
            default: {
                throw unicode_escape_error{"'U' or 'u' is expected."};
            }
        }
    }
}
