#pragma once

#include <string>
#include <memory>
#include <vector>

#include <ratl/json.h>
#include <ratl/rest/Request.h>
#include <ratl/rest/Response.h>
#include <ratl/rest/Router.h>

#include <ratl/server/RequestHandler.h>

namespace ratl {
    namespace rest {

        class RestAPI : public ratl::server::RequestHandler {

        public:
            RestAPI();

            Response process(const Request& request) noexcept override ;

            void use(std::unique_ptr<ratl::rest::Router>&& router) noexcept ;

        private:
            std::vector<std::unique_ptr<ratl::rest::Router>> _routers;
            std::vector<std::shared_ptr<ratl::rest::Resource>> _resources;
        };
    }
}