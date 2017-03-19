#include <ratl/rest/RestAPI.h>

using ratl::rest::RestAPI;
using ratl::rest::Response;
using ratl::rest::Router;


RestAPI::RestAPI()
    : _routers()
    , _resources()
{
}

Response RestAPI::process(const Request &request) const noexcept {

    for (auto const& resource : _resources) {
        if (resource->match(request.uri_)) {
            if (request.method_ != resource->method) {
                return Response::methodNotAllowed();
            }
            auto req = request;
            req.init(*resource);
            return resource->impl(req);
        }
    }

    return Response::notFound();
}

void RestAPI::use(std::unique_ptr<Router>&& router) noexcept {
    const auto& resources = router->_routes;
    _routers.push_back(std::move(router));
    _resources.insert(_resources.end(), resources.begin(), resources.end());
}