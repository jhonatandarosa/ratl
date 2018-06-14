#include "RTrieException.h"

using namespace ratl::router;

RTrieException::RTrieException(const std::string &__arg)
        : std::logic_error(__arg)
{}