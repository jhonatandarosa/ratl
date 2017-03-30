#include <catch.hpp>

#include <ratl/server/RestServer.h>
#include <thread>

#include "../../mock/MockNetIO.h"

using ratl::server::RestServer;

// gmock
using ::testing::NiceMock;

TEST_CASE( "ServerTest" ) {

    SECTION("Bind a server to an available address and port") {

        auto netIO = std::make_shared<MockNetIO>();
        EXPECT_CALL(*netIO, bind("localhost", 8000)).Times(1);

        RestServer server{netIO};

        CHECK_NOTHROW(server.bind("localhost", 8000));

        CHECK(::testing::Mock::VerifyAndClearExpectations(netIO.get()));
    }

    SECTION("Start a server without bind to an specific address and port must throws std::logic_error") {

        auto netIO = std::make_shared<NiceMock<MockNetIO>>();
        RestServer server{netIO};

        CHECK_THROWS_AS(server.run(), std::logic_error);

    }

    SECTION("Start a server after bind to an specific address and port") {

        std::shared_ptr<MockNetIO> netIO = std::make_shared<NiceMock<MockNetIO>>();
        EXPECT_CALL(*netIO, run()).Times(1);

        RestServer server{netIO};
        server.bind("localhost", 8000);

        CHECK_FALSE(server.isRunning());

        CHECK_NOTHROW(server.run());

        CHECK(server.isRunning());

        CHECK(::testing::Mock::VerifyAndClearExpectations(netIO.get()));

    }

    SECTION("Stop a server that is not running") {
        auto netIO = std::make_shared<NiceMock<MockNetIO>>();


        RestServer server{netIO};

        CHECK_FALSE(server.isRunning());
        CHECK_THROWS_AS(server.stop(), std::logic_error);

        CHECK(::testing::Mock::VerifyAndClearExpectations(netIO.get()));
    }

    SECTION("Stop a server that started successfully and is running") {
        auto netIO = std::make_shared<NiceMock<MockNetIO>>();
        EXPECT_CALL(*netIO, stop()).Times(1);
        
        RestServer server{netIO};
        server.bind("localhost", 8000);

        server.run();

        CHECK(server.isRunning());

        CHECK_NOTHROW(server.stop());

        CHECK_FALSE(server.isRunning());

        CHECK(::testing::Mock::VerifyAndClearExpectations(netIO.get()));
    }
}