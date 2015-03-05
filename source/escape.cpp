#include "unicode.hpp"
#include "cast.hpp"

namespace so {
    namespace {
        template<typename in_t>
        std::string escape(const in_t& literals, char prefix, int width) {
            std::string s;
            s.reserve(literals.length() * (2 + width));
            for (auto c : literals) {
                s += '\\';
                s += prefix;
                auto count = width;
                while (count--) {
                    auto q = c >> count * 4 & 0xF;
                    s += (q < 10 ? '0' : 'A' - 10) + q;
                }
            }
            return s;
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
                    throw unicode_cast_error{"Hexadigit (0-9, A-F, or a-f) is expected."};
                }
            }
            return value;
        }
    }

    std::string escape(const std::u16string& utf16) {
        return escape(utf16, 'u', 4);
    }

    std::string escape(const std::u32string& utf32) {
        return escape(utf32, 'U', 8);
    }

    char32_t escaped(u8i_t& literals) {
        if (*literals != '\\') {
            throw unicode_cast_error{"Back slash (\\) is expected."};
        }
        switch (*++literals) {
            case 'U': {
                return hex(++literals, 8);
            }
            case 'u': {
                char32_t code = hex(++literals, 4);
                if (is::high_surrogate(code)) {
                    code = utf32(code, escaped(literals)); // TODO refactoring
                }
                return code;
            }
            default: {
                throw unicode_cast_error{"'U' or 'u' is expected."};
            }
        }
    }
}
