#pragma once

#include <string>

namespace ratl {
    namespace router {
        class RTrieNode {

        public:
            explicit RTrieNode(const std::string& value, bool param=false);
            ~RTrieNode();

            void setEndpoint(bool endpoint) noexcept ;
            bool isEndpoint() const noexcept ;

            void append(RTrieNode* node) noexcept ;
            bool match(const std::string& token) const noexcept ;
            const RTrieNode* find(const std::string& token) const noexcept ;

        private:
            RTrieNode* find(const std::string& token) noexcept ;
            friend class RTrie;

        private:
            class Data;
            Data* d;
        };
    }
}