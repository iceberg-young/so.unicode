#include <iconv.h>
#include "unicode.hpp"

namespace so {
    class ic_raii
    {
    public:
        using name_t = const char*;

    public:
        ic_raii(name_t target, name_t source) :
          ic(iconv_open(target, source)) {
        }

        ~ic_raii() {
            iconv_close(this->ic);
        }

    public:
        void reset() {
            iconv(this->ic, nullptr, nullptr, nullptr, nullptr);
        }

        std::string convert(const std::string& source) {
            std::string target;
            /*
            char* in = &wild[0];
            auto in_size = wild.size();
            std::string buffer(buffer_size);
            while (in_size) {
                char* out = &buffer[0];
                auto out_size = buffer.size();

                iconv(c.handle, &in, &in_size, &out, &out_size);

                auto length = buffer.size() - out_size;
                switch (errno) {
                    case E2BIG: {
                        if (!length) {
                            throw std::out_of_range("*Implementation Fault!*"
                              "The output buffer cannot hold a single character of the target encoding."
                            );
                        }
                        break;
                    }
                    case EILSEQ: {
                        throw std::range_error("An illegal sequence has been encountered"
                          " at [" + std::to_string(wild.size() - in_size) + "]"
                        );
                    }
                    case EINVAL: {
                        throw std::length_error("An incomplete sequence has been encountered"
                          " at [" + std::to_string(wild.size() - in_size) + "]"
                        );
                    }
                }

                target.append(buffer, length);
            }
            */
            return target;
        }

    private:
        iconv_t ic;
    };

    std::string utf8(const std::string& wild, const char* encoding) {
        std::string target;
        // TODO
        return target;
    }

    std::string wild(const std::string& utf8, const char* encoding) {
        std::string target;
        // TODO
        return target;
    }
}
