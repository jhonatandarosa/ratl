#pragma once

#include <string>
#include <type_traits>
#include <unordered_map>
#include <stdexcept>

namespace ratl {
    namespace rest {

        class Resource;
        class Request {
        public:
            Request(const std::string& uri, const std::string& method, const std::string& payload);
            void init(const Resource& resource) noexcept ;

            const bool empty() const noexcept ;
            const std::string& payload() const noexcept { return payload_; }

            template<typename T>
            T getParameter(const std::string& name) const throw(std::logic_error) {
                static_assert(std::is_same<T, std::string>::value, "Must be a string");
                static_assert(std::is_default_constructible<T>::value, "Must have a default constructor");
                return T();
            }

        // data
        private:
            const std::string uri_;
            const std::string method_;
            const std::string payload_;
            std::unordered_map<std::string, std::string> parameters_;

            friend class RestAPI;
        };

        template <>
        std::string Request::getParameter(const std::string &name) const throw(std::logic_error);
    }
}