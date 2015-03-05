#include <vector>
#include <iconv.h>
#include "unicode.hpp"

namespace so {
    namespace {
        class ic_raii
        {
        public:
            ic_raii(const char* source, const char* target) :
              ic(iconv_open(target, source)) {
            }

            ~ic_raii() {
                iconv_close(this->ic);
            }

        public:
            void convert(const std::string& source, std::string& target) {
                std::vector<char> buffer(std::max(source.size(), 8ul/*minimal reserve; arbitrary choice*/));
                auto in = const_cast<char*>(&source[0]);
                auto in_left = source.size();
                while (in_left) {
                    auto out = &buffer[0];
                    auto out_left = buffer.size();
                    iconv(this->ic, &in, &in_left, &out, &out_left);
                    auto length = buffer.size() - out_left;
                    if (length > 0) {
                        target.append(&buffer[0], length);
                    }
                    switch (errno) {
                        case E2BIG: {
                            if (length == 0) {
                                // The output buffer is too small to hold even a single character.
                                buffer.resize(buffer.size() * 2);
                            }
                            break;
                        }
                        case EILSEQ: {
                            throw unicode_cast_error("An illegal sequence has been encountered @"
                              + std::to_string(source.size() - in_left)
                            );
                        }
                        case EINVAL: {
                            throw unicode_cast_error("An incomplete sequence has been encountered @"
                              + std::to_string(source.size() - in_left)
                            );
                        }
                    }
                }
            }

        private:
            iconv_t ic;
        };
    }

    std::string utf8(const std::string& mbcs, const char* encoding) {
        std::string target;
        ic_raii i(encoding, "UTF-8");
        i.convert(mbcs, target);
        return target;
    }

    std::string mbcs(const std::string& utf8, const char* encoding) {
        std::string target;
        ic_raii i("UTF-8", encoding);
        i.convert(utf8, target);
        return target;
    }
}
