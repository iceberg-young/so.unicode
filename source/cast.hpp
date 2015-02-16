#ifndef INCLUDE_SO_UNICODE_CAST_ONCE_FLAG
#define INCLUDE_SO_UNICODE_CAST_ONCE_FLAG

namespace so {
    template<typename Tout, typename Tin>
    inline Tout utf32_indirect(const Tin& in) {
        Tout out;
        out.reserve(in.size());
        auto i = in.cbegin();
        auto e = in.cend();
        while (i != e) {
            out += utf32(i);
        }
        return out;
    }

    template<typename Tout>
    inline Tout utf32_direct(const std::u32string& in) {
        Tout out;
        out.reserve(in.size());
        for (auto c : in) {
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
