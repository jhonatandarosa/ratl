#include <catch.hpp>

#include <ratl/server/RestServer.h>

#include "../../mock/MockNetIO.h"

using ratl::server::RestServer;

TEST_CASE( "ServerTest" ) {

    SECTION("Create a server with default NetIO layer") {

//        RestServer server;
    }

    SECTION("Create a server with specific NetIO layer") {

        RestServer<MockNetIO> server;
    }

}