#pragma once

#include <ratl/server/NetIO.h>

struct mg_connection;

namespace ratl {
    namespace server {
        namespace mongoose {
            class MongooseNetIO : public ratl::server::NetIO {
            public:
                explicit MongooseNetIO();
                ~MongooseNetIO();

                void bind(const std::string &address, const int port) override ;
                void run() override ;
                void stop() override ;

            protected:
                void setRequestHandler(const std::shared_ptr<RequestHandler> &handler) override;

            private:
                class Impl;
                Impl* pImpl;
            };
        }
    }
}