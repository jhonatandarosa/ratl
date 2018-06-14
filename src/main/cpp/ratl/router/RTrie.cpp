#include "RTrie.h"
#include "RTrieException.h"
#include "RTrieNode.h"
#include <sstream>


using namespace ratl::router;

bool isArgument(const std::string& token) {
    return token[0] == '<' && token[token.size()-1] == '>';
}

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

    while (std::getline(in, token, '/')) {
        if (token.empty()) {
            throw RTrieException("empty token");
        }

        bool isArgumentToken = isArgument(token);

        auto node = current->find(token);
        if (node) {
            current = node;
        } else {
            node = new RTrieNode(token, isArgumentToken);
            current->append(node);
            current = node;
        }
    }

    current->setEndpoint(true);
}


const RTrieNode* RTrie::match(const std::string& path) {
    std::string token;
    std::istringstream in(path);

    std::getline(in, token, '/');
    const RTrieNode* current = &d->root;

    while (current && std::getline(in, token, '/')) {
        current = current->find(token);
    }

    if (current && current->isEndpoint()) {
        return current;
    }
    // not found
    return nullptr;
}