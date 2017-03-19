#pragma once

#include <ratl/json.h>

namespace ratl {
    namespace rest {
        struct Response {
            ratl::json content;
            int httpCode;

            static Response ok(const ratl::json& response={}) { return {response, 200}; }

            static Response badRequest() noexcept { return status(400); }
            static Response notFound() noexcept { return status(404); }
            static Response methodNotAllowed() noexcept { return status(405); }

        private:
            static Response status(int code) noexcept { return {ratl::json{}, code}; }
        };
    }
}