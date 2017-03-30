#include <ratl/server/RestServer.h>

using ratl::server::RestServer;
using ratl::server::NetIO;


RestServer::RestServer(const std::shared_ptr<NetIO>& netIO)
    : netIO{netIO}
    , bound{}
    , running{}
{
}

void RestServer::bind(const std::string &address, const int port) {
    netIO->bind(address, port);
    bound = true;
}

void RestServer::run() throw(std::logic_error) {
    if (!bound) {
        throw std::logic_error{"Server not bound to an address"};
    }
    netIO->run();
    running = true;
}

void RestServer::stop() throw(std::logic_error) {
    if (!running) {
        throw std::logic_error{"Server is not running!"};
    }
    netIO->stop();
    running = false;
}


const bool RestServer::isRunning() const noexcept {
    return running;
}
