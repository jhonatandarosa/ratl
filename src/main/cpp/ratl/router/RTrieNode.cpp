#include "RTrieNode.h"
#include "RTrieException.h"

#include <vector>

using namespace ratl::router;

struct TokenData {
    std::string name;
    std::string pattern;
};

bool isParameterToken(const std::string &token) {
    return token[0] == '<' && token[token.size()-1] == '>';
}

TokenData extractTokenData(const std::string& token) {
    auto name = token.substr(1, token.size() - 2);
    return {name, ""};
}

class RTrieNode::Data {
public:

    Data(const std::string& value)
        : value(value)
        , name()
        , pattern()
        , param(isParameterToken(value))
        , endpoint(false)
        , children()
    {
        if (param) {
            initParamData();
        }
    }

    std::string value;
    std::string name;
    std::string pattern;
    bool param;
    bool endpoint;
    std::vector<RTrieNode*> children;


    void initParamData() {
        auto tokenData = extractTokenData(value);
        name = tokenData.name;
        pattern = tokenData.pattern;
    }
};

RTrieNode::RTrieNode(const std::string &value)
    : d(new Data(value))
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
    if (node->d->param) {
        d->children.push_back(node);
    } else {
        d->children.insert(d->children.begin(), node);
    }
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

bool RTrieNode::isParameterNode() const noexcept {
    return d->param;
}

const std::string& RTrieNode::name() const noexcept {
    return d->name;
}

RTrieNode* RTrieNode::findChild(const std::string& token) {
    auto isParamToken = isParameterToken(token);
    for (auto child : d->children) {
        if (child->d->value == token) {
            return child;
        }
        if (isParamToken && child->d->param) {
            auto tokenData = extractTokenData(token);
            if (tokenData.name == child->d->name || tokenData.pattern == child->d->pattern) {
                if (tokenData.name != child->d->name || tokenData.pattern != child->d->pattern) {
                    throw RTrieException("Parameters node on the same point must have same <name:pattern>");
                }
                return child;
            }
        }
    }
    return nullptr;
}