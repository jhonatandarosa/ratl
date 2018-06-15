#pragma once

#include <string>
#include <unordered_map>

namespace ratl {
    namespace router {
        class RTrieNode;

        class RTrieMatch {
            friend class RTrie;

            RTrieMatch();

        public:

            ~RTrieMatch();

            // move
            RTrieMatch(RTrieMatch&& rhs) noexcept ;
            RTrieMatch& operator=(RTrieMatch&& rhs) noexcept ;

            // disable copy
            RTrieMatch(const RTrieMatch& rhs) = delete;
            RTrieMatch& operator=(const RTrieMatch& rhs) = delete;

            // equality operators
            bool operator==(const RTrieMatch &rhs) const;
            bool operator!=(const RTrieMatch &rhs) const;

            // bool related operators
            explicit operator bool() const;
            bool operator !() const;


            // param related
            const std::unordered_map<std::string, std::string>& params() const noexcept ;

        private:
            void addParameter(const std::string& name, const std::string& value) noexcept ;
            void validated(const RTrieNode*node) noexcept ;

        private:
            class Data;
            Data* d;
        };
    }
}