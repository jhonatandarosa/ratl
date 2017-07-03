#include <ratl/server/RestServer.h>

#include <ratl/server/RequestHandler.h>

using ratl::server::RestServer;
using ratl::server::NetIO;


RestServer::RestServer(const std::shared_ptr<NetIO>& netIO)
    : netIO{netIO}
    , bound{}
    , running{}
    , handler{}
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
    if (!handler) {
        throw std::logic_error{"Handler not configured"};
    }
    running = true;
    netIO->run();
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


void RestServer::use(std::unique_ptr<ratl::server::RequestHandler> handler) noexcept {
    this->handler = std::move(handler);
    netIO->setRequestHandler(this->handler);
}