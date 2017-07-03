#pragma once

#include <type_traits>
#include <string>
#include <memory>
#include <stdexcept>
#include <vector>

#include <ratl/server/NetIO.h>

namespace ratl {
    namespace rest {
        class Request;
        class Response;
    }

    namespace server {

        class RequestHandler;

        class RestServer {
        public:
            RestServer(const std::shared_ptr<NetIO>& netIO);

            void bind(const std::string& address, const int port);
            void run() throw(std::logic_error);
            void stop() throw(std::logic_error);

            const bool isRunning() const noexcept;

            void use(std::unique_ptr<ratl::server::RequestHandler> handler) noexcept ;

        private:
            std::shared_ptr<NetIO> netIO;
            bool bound;
            bool running;
            std::shared_ptr<ratl::server::RequestHandler> handler;
        };

    }
}