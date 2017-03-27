#pragma once

#include <type_traits>
#include <string>

#include <ratl/server/NetIO.h>

namespace ratl {
    namespace server {
        template <class NetIOLayer>
        class RestServer {
            static_assert(std::is_base_of<NetIO, NetIOLayer>::value, "NetIOLayer must implement NetIO interface");

        public:
            ~RestServer() {};
            void bind(const std::string& address, const int port);
            void start();
            void stop();
        };

    }
}