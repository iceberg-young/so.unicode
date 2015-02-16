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
            void reset() {
                iconv(this->ic, nullptr, nullptr, nullptr, nullptr);
            }

            void convert(const std::string& source, std::string& target) {
                constexpr size_t BUFFER_MIN_SIZE = 8;
                std::vector<char> buffer(std::max(source.size(), BUFFER_MIN_SIZE));
                auto in = const_cast<char*>(&source[0]);
                auto in_size = source.size();
                while (in_size) {
                    auto out = &buffer[0];
                    auto out_size = buffer.size();
                    iconv(this->ic, &in, &in_size, &out, &out_size);
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
                            throw std::range_error("An illegal sequence has been encountered @"
                              + std::to_string(source.size() - in_size)
                            );
                        }
                        case EINVAL: {
                            throw std::length_error("An incomplete sequence has been encountered @"
                              + std::to_string(source.size() - in_size)
                            );
                        }
                    }
                    target.append(&buffer[0], length);
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
