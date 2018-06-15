#pragma once

namespace ratl {
    namespace router {
        class RTrieNode;

        class RTrieMatch {
            friend class RTrie;

            explicit RTrieMatch(const RTrieNode*const node = nullptr);

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

        private:
            class Data;
            Data* d;
        };
    }
}