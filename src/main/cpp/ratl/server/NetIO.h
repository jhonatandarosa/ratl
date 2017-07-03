#pragma once

#include <string>
#include <memory>

namespace ratl {
    namespace server {
        class RequestHandler;

        class NetIO {
        public:
            virtual ~NetIO() = default;

        protected:
            virtual void bind(const std::string& address, const int port) = 0;
            virtual void run() = 0;
            virtual void stop() = 0;
            virtual void setRequestHandler(const std::shared_ptr<RequestHandler>&) = 0;

            friend class RestServer;
        };
    }
}