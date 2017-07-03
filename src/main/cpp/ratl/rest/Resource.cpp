#include <ratl/rest/Resource.h>
#ifdef _USE_BOOST_REGEX
#include <boost/regex.hpp>
namespace std {
    using boost::regex;
    using boost::smatch;
//    using boost::regex_search;
    using boost::regex_match;
}
#else
#include <regex>
#endif

using ratl::rest::Resource;

const std::string SIMPLE_PATH_PARAM_PATTERN = "([\\w\\d-]+)";

Resource::Resource(const std::string &uri_, const std::string &method_, const ratl::rest::ResourceFunction &impl_)
        : parameters{}
        , uri{uri_}
        , method{method_}
        , impl{impl_}
        , pattern{createPattern()}
{
}

bool Resource::match(const std::string& uri) const noexcept {
    return std::regex_match(uri, std::regex{pattern});
}

std::string Resource::param(int idx) const noexcept {
    return parameters[idx];
}

std::string Resource::createPattern() noexcept {
    using std::regex;
    using std::smatch;

    auto start = uri.cbegin();
    auto end   = uri.cend();
    std::string pattern = "";

    regex re("/([^/]+)+");
    smatch what;
    auto uriStart = uri.cbegin();
    auto last = start;
    while (regex_search(start, end, what, re)) {
        const auto part = what[1].str();
        if (part[0] == '<' && part[part.size()-1] == '>') {
            uriStart += std::distance(last, start) + 1;

            const auto name = part.substr(1, part.size() - 2);
//            const auto us = uriStart;
//            const auto ue = std::find(uriStart+1, uri.cend(), '/');
//            const auto value = std::string(us, ue);
            parameters.push_back(name);
//            parameters_.insert({name, value});
            pattern += "/" + SIMPLE_PATH_PARAM_PATTERN;
        } else {
            pattern += std::string{what[0].first, what[0].second};
        }
        start = what[0].second;
    }
    if (pattern.empty()) {
        pattern = "/";
    }
    return pattern;
}
