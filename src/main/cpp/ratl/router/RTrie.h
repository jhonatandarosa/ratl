#pragma once

#include <string>


namespace ratl {
    namespace router {
        class RTrieException;
        class RTrieNode;

        class RTrie {

        public:
            RTrie();
            ~RTrie();

            void insertPath(const std::string& path);

            const RTrieNode* match(const std::string& path);


        private:
            class Data;
            Data* d;
        };

    }
}