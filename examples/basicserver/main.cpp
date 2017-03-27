#include <iostream>

#include <ratl/server/RestServer.h>

#include <ratl/server/asio/BoostASIONetIO.h>

int main(int argc, char** argv) {

    using ratl::server::asio::BoostASIONetIO;

    ratl::server::RestServer<BoostASIONetIO> server;

    return 0;
}