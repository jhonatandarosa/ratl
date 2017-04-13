#include <ratl/server/asio/BoostASIONetIO.h>

#include "detail/server.hpp"

using ratl::server::asio::BoostASIONetIO;

class BoostASIONetIO::Impl {
public:
    Impl()
        : server{}
    {
    }

    http::server::server server;
};

BoostASIONetIO::~BoostASIONetIO() {
    delete pImpl;
}

void BoostASIONetIO::bind(const std::string &address, const int port) {
    pImpl->server.initialize(address, std::to_string(port));
}

void BoostASIONetIO::run() {
    pImpl->server.run();
}

void BoostASIONetIO::stop() {

}
