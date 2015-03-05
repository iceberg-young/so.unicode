#ifndef INCLUDE_SO_UNICODE_CAST_ONCE_FLAG
#define INCLUDE_SO_UNICODE_CAST_ONCE_FLAG

namespace so {
    template<typename out_t, typename in_t>
    inline out_t utf32_indirect(const in_t& in) {
        out_t out;
        out.reserve(in.size());
        auto i = in.begin();
        auto e = in.end();
        while (i != e) {
            out += utf32(i);
        }
        return out;
    }

    template<typename out_t>
    inline out_t utf32_direct(const std::u32string& in) {
        out_t out;
        out.reserve(in.size());
        for (auto c : in) {
            out += c;
        }
        return out;
    }

    template<typename out_t>
    inline out_t utf32_single(char32_t code) {
        out_t out;
        return out += code;
    }

    inline char32_t utf32(char16_t high, char16_t low) {
        if (!is::high_surrogate(high)) {
            throw unicode_cast_error{std::to_string(high) + " is not a valid high surrogate."};
        }
        if (!is::low_surrogate(low)) {
            throw unicode_cast_error{std::to_string(low) + " is not a valid low surrogate."};
        }
        return 0x10000 + ((high - 0xD800) << 10) + (low - 0xDC00);
    }
}

#endif//INCLUDE_SO_UNICODE_CAST_ONCE_FLAG
