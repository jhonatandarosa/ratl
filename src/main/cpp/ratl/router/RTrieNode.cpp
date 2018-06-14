#include "RTrieNode.h"

#include <vector>

using namespace ratl::router;

class RTrieNode::Data {
public:

    Data(const std::string& value, bool param)
        : value(value)
        , param(param)
        , endpoint(false)
        , children()
    {}

    std::string value;
    bool param;
    bool endpoint;
    std::vector<RTrieNode*> children;
};

RTrieNode::RTrieNode(const std::string &value, bool param)
    : d(new Data(value, param))
{
}

RTrieNode::~RTrieNode() {
    for (auto node : d->children) {
        delete node;
    }
    delete d;
}

void RTrieNode::setEndpoint(const bool endpoint) noexcept {
    d->endpoint = endpoint;
}

bool RTrieNode::isEndpoint() const noexcept {
    return d->endpoint;
}

void RTrieNode::append(RTrieNode* node) noexcept {
    d->children.push_back(node);
}

bool RTrieNode::match(const std::string& token) const noexcept {
    if (d->param) return true;
    return d->value == token;
}

const RTrieNode* RTrieNode::find(const std::string& token) const noexcept {
    for (auto child : d->children) {
        if (child->match(token)) {
            return child;
        }
    }
    return nullptr;
}

RTrieNode* RTrieNode::find(const std::string& token) noexcept {
    for (auto child : d->children) {
        if (child->match(token)) {
            return child;
        }
    }
    return nullptr;
}