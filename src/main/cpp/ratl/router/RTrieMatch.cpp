#include "RTrieMatch.h"
#include "RTrieNode.h"

using namespace ratl::router;

class RTrieMatch::Data {
public:

    const RTrieNode* node{};
    std::unordered_map<std::string, std::string> params{};
};

RTrieMatch::RTrieMatch()
    : d(new Data)
{
}

RTrieMatch::~RTrieMatch() {
    delete d;
}

RTrieMatch::RTrieMatch(RTrieMatch&& rhs) noexcept
    : d(rhs.d)
{
    rhs.d = nullptr;
}

RTrieMatch& RTrieMatch::operator=(RTrieMatch&& rhs) noexcept {
    std::swap(d, rhs.d);
    return *this;
}

bool RTrieMatch::operator==(const RTrieMatch &rhs) const {
    return d->node == rhs.d->node;
}

bool RTrieMatch::operator!=(const RTrieMatch &rhs) const {
    return !(rhs == *this);
}


RTrieMatch::operator bool() const {
    return d->node != nullptr;
}

bool RTrieMatch::operator!() const {
    return !this;
}

const std::unordered_map<std::string, std::string>& RTrieMatch::params() const noexcept {
    return d->params;
}

void RTrieMatch::addParameter(const std::string& name, const std::string& value) noexcept {
    d->params.insert({name, value});
}

void RTrieMatch::validated(const RTrieNode* node) noexcept {
    d->node = node;
}