#pragma once

#include <string>

#include "RTrieMatch.h"

namespace ratl {
    namespace router {
        class RTrieException;

        class RTrie {

        public:
            RTrie();
            ~RTrie();

            void insertPath(const std::string& path);

            RTrieMatch match(const std::string& path);


        private:
            class Data;
            Data* d;
        };

    }
}