#pragma once

#include <string>

namespace ratl {
    namespace router {
        class RTrieNode {

        public:
            explicit RTrieNode(const std::string& value);
            ~RTrieNode();

            void setEndpoint(bool endpoint) noexcept ;
            bool isEndpoint() const noexcept ;

            void append(RTrieNode* node) noexcept ;

            bool match(const std::string& token) const noexcept ;
            const RTrieNode* find(const std::string& token) const noexcept ;

            bool isParameterNode() const noexcept ;
            const std::string& name() const noexcept ;

        private:
            RTrieNode* findChild(const std::string& token) ;

            friend class RTrie;

        private:
            class Data;
            Data* d;
        };
    }
}