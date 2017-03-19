#pragma once

#include <string>
#include <memory>
#include <functional>
#include <vector>

#include <ratl/rest/Request.h>
#include <ratl/rest/Response.h>
#include <ratl/rest/Resource.h>

namespace ratl {
    namespace rest {

        class RestAPI;

        class Router {

        public:
            Router();
            virtual ~Router();

            void route (const std::string& uri, const std::string& method, const std::function<ratl::rest::Response(const ratl::rest::Request&)>& handler) noexcept;

            const bool empty() const noexcept ;
            const std::size_t size() const noexcept ;

        protected:
            template <class T>
            void route (const std::string& uri, const std::string& method, ratl::rest::Response(T::* handler)(const ratl::rest::Request&)) {
                route(uri, method, std::bind(handler, dynamic_cast<T*>(this), std::placeholders::_1));
            }


        private:
            std::vector<std::shared_ptr<Resource>> _routes;

            friend ratl::rest::RestAPI;
        };
    }
}