#pragma once

#include <string>

namespace ratl {
    namespace server {
        class NetIO {
        public:
            virtual ~NetIO();
            virtual void bind(const std::string& address, const int port) = 0;
            virtual void run() = 0;
            virtual void stop() = 0;
        };
    }
}