#pragma once

#include <string>
#include <functional>
#include <vector>

#include <ratl/rest/Request.h>
#include <ratl/rest/Response.h>

namespace ratl {
    namespace rest {
        class RestAPI;

        using ResourceFunction = std::function<ratl::rest::Response(const ratl::rest::Request&)>;

        class Resource {
        public:
            Resource(const std::string &uri, const std::string &method, const ResourceFunction &impl);


        private:
            std::vector<std::string> parameters;
        public:
            const std::string uri;
            const std::string method;
            const ResourceFunction impl;
            const std::string pattern;

        public:
            bool match(const std::string& uri) const noexcept ;
            std::string param(int idx) const noexcept ;
        private:
            std::string createPattern() noexcept;
        };
    }
}
