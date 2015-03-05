#include "unicode.hpp"
#include "cast.hpp"

namespace so {
    namespace unicode {
        namespace {
            template<typename in_t>
            std::string escape(const in_t& literals, char prefix) {
                std::string s;
                constexpr auto width = sizeof(typename in_t::value_type) * 2;
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

            template<typename out_t>
            out_t hex(u8i_t& literals) {
                out_t value = 0;
                for (int i = 0; i < sizeof(out_t) * 2; ++i, ++literals) {
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
            return escape(utf16, 'u');
        }

        std::string escape(const std::u32string& utf32) {
            return escape(utf32, 'U');
        }

        char32_t escaped(u8i_t& literals) {
            if (*literals != '\\') {
                throw unicode_cast_error{"Back slash (\\) is expected."};
            }
            switch (*++literals) {
                case 'U': {
                    return hex<char32_t>(++literals);
                }
                case 'u': {
                    char16_t code = hex<char16_t>(++literals);
                    if (not is::high_surrogate(code)) return code;
                    if (*literals != '\\') {
                        throw unicode_cast_error{"Back slash (\\) is expected, for low surrogate."};
                    }
                    if (*++literals != 'u') {
                        throw unicode_cast_error{"'u' is expected, for low surrogate."};
                    }
                    return utf32(code, hex<char16_t>(++literals));
                }
                default: {
                    throw unicode_cast_error{"'U' or 'u' is expected."};
                }
            }
        }
    }
}
