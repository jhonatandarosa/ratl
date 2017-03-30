#include <iostream>
#include <memory>

#include <ratl/server/RestServer.h>

#include <ratl/server/asio/BoostASIONetIO.h>

int main(int argc, char** argv) {

    using ratl::server::asio::BoostASIONetIO;
    auto netIO = std::make_shared<BoostASIONetIO>();
    ratl::server::RestServer server{netIO};

    server.bind("0.0.0.0", 8000);

    server.run();

    return 0;
}