#include <ratl/rest/Request.h>

#ifdef _USE_BOOST_REGEX
#include <boost/regex.hpp>
namespace std {
    using boost::regex;
    using boost::smatch;
}
#else
#include <regex>
#endif
#include "Resource.h"

using namespace ratl::rest;

Request::Request(const std::string &uri, const std::string &method, const std::string &payload)
    : uri_(uri)
    , method_(method)
    , payload_(payload)
    , parameters_()
{
}

const bool Request::empty() const noexcept {
    return payload_.empty();
}

void Request::init(const ratl::rest::Resource& resource) noexcept {

    assert(resource.match(uri_));

    using std::regex;
    using std::smatch;

    smatch matches;
    if (regex_match(uri_, matches, regex{resource.pattern})){
        for (std::size_t i = 1; i < matches.size(); i++) {
            auto value = matches[i].str();
            auto name = resource.param(i-1);
            parameters_.insert({name, value});
        }
    }
}


template <>
std::string Request::getParameter(const std::string &name) const throw(std::logic_error) {
    const auto it = parameters_.find(name);
    if (it != parameters_.end()) return it->second;
    throw std::logic_error("Parameter with id not found");
}