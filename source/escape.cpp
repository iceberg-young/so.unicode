/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "utf.hpp"
#include "cast.hpp"

namespace so {
    namespace utf {
        namespace {
            constexpr int bits_per_digit = 4;
            constexpr int digits_per_byte = 2;
            constexpr char hex_digits[]{"0123456789ABCDEF"};

            template<typename in_t>
            std::string encode(const in_t& literals, char prefix) {
                constexpr int width = sizeof(typename in_t::value_type) * digits_per_byte;

                std::string s;
                s.reserve(literals.length() * (width + 2)); // +2: "\u" or "\U"
                for (auto c : literals) {
                    (s += '\\') += prefix;
                    int count = width;
                    while (count--) {
                        auto q = c >> (count * bits_per_digit);
                        s += hex_digits[q & 0xF];
                    }
                }
                return s;
            }

            template<typename out_t>
            out_t decode(u8i_t& literals) {
                out_t value = 0;
                for (int i = 0; i < sizeof(out_t) * digits_per_byte; ++i, ++literals) {
                    value <<= bits_per_digit;
                    char quad = *literals;
                    if (quad >= '0' and quad <= '9') {
                        value += quad - '0';
                    }
                    else if (quad >= 'A' and quad <= 'F') {
                        value += quad - 'A' + 0xA;
                    }
                    else if (quad >= 'a' and quad <= 'f') {
                        value += quad - 'a' + 0Xa;
                    }
                    else {
                        throw unicode_cast_error{
                          "Hexadigit (0-9, A-F, or a-f) is expected."
                        };
                    }
                }
                return value;
            }
        }

        std::string escape(const std::u16string& utf16) {
            return encode(utf16, 'u');
        }

        std::string escape(const std::u32string& utf32) {
            return encode(utf32, 'U');
        }

        char32_t escaped(u8i_t& literals) {
            if (*literals != '\\') {
                throw unicode_cast_error{"Back slash (\\) is expected."};
            }
            switch (*++literals) {
                case 'U': {
                    return decode<char32_t>(++literals);
                }
                case 'u': {
                    char16_t code = decode<char16_t>(++literals);
                    if (not is::high_surrogate(code)) return code;
                    if (*literals != '\\') {
                        throw unicode_cast_error{
                          "Back slash (\\) is expected, for low surrogate."
                        };
                    }
                    if (*++literals != 'u') {
                        throw unicode_cast_error{
                          "'u' is expected, for low surrogate."
                        };
                    }
                    return utf32(code, decode<char16_t>(++literals));
                }
                default: {
                    throw unicode_cast_error{"'U' or 'u' is expected."};
                }
            }
        }
    }
}
