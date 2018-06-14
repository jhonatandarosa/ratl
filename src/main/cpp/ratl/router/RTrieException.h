#pragma once

#include <stdexcept>

namespace ratl{
    namespace router {
        class RTrieException : public std::logic_error {

        public:
            explicit RTrieException(const std::string &__arg);
        };

    }
}