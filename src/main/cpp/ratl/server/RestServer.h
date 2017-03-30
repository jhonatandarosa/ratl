#pragma once

#include <type_traits>
#include <string>
#include <memory>
#include <stdexcept>

#include <ratl/server/NetIO.h>

namespace ratl {
    namespace server {
        class RestServer {
        public:
            RestServer(const std::shared_ptr<NetIO>& netIO);

            void bind(const std::string& address, const int port);
            void run() throw(std::logic_error);
            void stop() throw(std::logic_error);

            const bool isRunning() const noexcept;

        private:
            std::shared_ptr<NetIO> netIO;
            bool bound;
            bool running;
        };

    }
}