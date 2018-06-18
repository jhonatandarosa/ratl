#include "RTrie.h"

#include <sstream>
#include <algorithm>
#include <unordered_set>

#include "RTrieException.h"
#include "RTrieNode.h"


using namespace ratl::router;

class RTrie::Data {
public:
    RTrieNode root{"/"};
};

RTrie::RTrie()
    : d(new Data)
{
}

RTrie::~RTrie()
{;
    delete d;
}

void RTrie::insertPath(const std::string &path) {
    if (path.empty()) {
        throw RTrieException("Invalid path");
    }

    if (path[0] != '/') {
        throw RTrieException("Invalid path");
    }

    std::string token;
    std::istringstream in(path);
    RTrieNode* current = &d->root;
    std::getline(in, token, '/');
    std::unordered_set<std::string> tokens;

    while (std::getline(in, token, '/')) {
        if (token.empty()) {
            throw RTrieException("Invalid path");
        }

        auto node = current->findChild(token);
        if (node) {
            current = node;
        } else {
            if (tokens.insert(token).second) {
                node = new RTrieNode(token);
                current->append(node);
                current = node;
            } else {
                throw RTrieException("Duplicated parameter name");
            }
        }
    }
    if (current->isEndpoint() &&
        path[path.size()-1] != '/')// ignore trailing '/'
    {
        throw RTrieException("Duplicated route path");
    }
    current->setEndpoint(true);
}


RTrieMatch RTrie::match(const std::string& path) {
    std::string token;
    std::istringstream in(path);

    std::getline(in, token, '/');
    const RTrieNode* current = &d->root;

    RTrieMatch match;

    while (std::getline(in, token, '/')) {
        current = current->find(token);
        if (!current) break;

        if (current->isParameterNode()) {
            auto names = current->names();
            std::for_each(names.begin(), names.end(), [&](const auto& name){
                match.addParameter(name, token);
            });
        }
    }

    if (current && current->isEndpoint()) {
        match.validated(current);
        return match;
    }
    // not found
    return RTrieMatch{};
}