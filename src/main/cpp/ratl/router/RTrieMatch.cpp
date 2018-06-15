#include "RTrieMatch.h"
#include "RTrieNode.h"

using namespace ratl::router;

class RTrieMatch::Data {
public:
    Data(const RTrieNode* const node_)
        :node(node_)
    {}

    const RTrieNode* const node;
};

RTrieMatch::RTrieMatch(const RTrieNode* const node)
    : d(new Data{node})
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
