#include <ratl/rest/Router.h>

using ratl::rest::Router;
using ratl::rest::Request;
using ratl::rest::Response;
using ratl::rest::Resource;

Router::Router()
    : _routes()
{
}

Router::~Router() {
}

void Router::route(const std::string &uri, const std::string &method, const std::function<Response(const Request &)> &handler) noexcept {
    _routes.push_back(std::make_shared<Resource>(uri, method, handler));
}

const bool Router::empty() const noexcept {
    return _routes.empty();
}

const std::size_t Router::size() const noexcept {
    return _routes.size();
}
