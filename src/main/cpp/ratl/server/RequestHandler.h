#pragma once

namespace ratl {
    namespace rest {
        class Request;
        class Response;
    }

    namespace server {
        class RequestHandler {
        public:
            virtual ratl::rest::Response process(const ratl::rest::Request&) noexcept = 0;
        };
    }
}