#pragma once

#include <ratl/server/NetIO.h>

namespace ratl {
    namespace server {
        namespace asio {
            class BoostASIONetIO : public ratl::server::NetIO {
            public:
                ~BoostASIONetIO();

                void bind(const std::string &address, const int port) override ;
                void run() override ;
                void stop() override ;

            private:
                class Impl;
                Impl* pImpl;
            };
        }
    }
}