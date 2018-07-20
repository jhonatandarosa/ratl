#include <iostream>
#include <memory>

#include <ratl/rest/RestAPI.h>
#include <ratl/rest/Router.h>
#include <ratl/rest/Request.h>
#include <ratl/rest/Response.h>
#include <ratl/server/RestServer.h>

#include <ratl/server/mongoose/MongooseNetIO.h>

int main(int argc, char** argv) {

    // init demux router
    using ratl::rest::Router;
    using ratl::rest::Request;
    using ratl::rest::Response;
    std::unique_ptr<Router> router{new Router{}};

    router->route("/", "GET", [](const Request& req) -> Response {
        return Response::ok({{"foo","bar"}});
    });

    // init api
    using ratl::rest::RestAPI;
    std::unique_ptr<RestAPI> api{new RestAPI{}};
    api->use(std::move(router));

    // init server
    using namespace ratl::server;
    RestServer server{std::make_shared<mongoose::MongooseNetIO>()};
    server.use(std::move(api));


    server.bind("0.0.0.0", 5002);

    server.run();

    return 0;
}