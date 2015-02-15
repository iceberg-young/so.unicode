#ifndef INCLUDE_SO_UNICODE_CAST_ONCE_FLAG
#define INCLUDE_SO_UNICODE_CAST_ONCE_FLAG

namespace so {
    template<typename Tout, typename Tin>
    inline Tout utf32_indirect(const Tin& in) {
        Tout out;
        auto i = in.cbegin();
        auto e = in.cend();
        while (i != e) {
            out += utf32(i);
        }
        return out;
    }

    template<typename Tout>
    inline Tout utf32_direct(const std::u32string& code) {
        Tout out;
        for (auto c : code) {
            out += c;
        }
        return out;
    }

    template<typename Tout>
    inline Tout utf32_single(char32_t code) {
        Tout out;
        return out += code;
    }
}

#endif//INCLUDE_SO_UNICODE_CAST_ONCE_FLAG
