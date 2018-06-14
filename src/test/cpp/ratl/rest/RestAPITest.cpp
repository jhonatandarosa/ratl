#include <catch.hpp>

#include <ratl/json.h>
#include <ratl/rest/RestAPI.h>
#include <ratl/rest/Router.h>
#include <ratl/rest/Response.h>

class TestRouter : public ratl::rest::Router {

public:
    TestRouter() {
        route("/test", "GET", &TestRouter::test);
    }

    ratl::rest::Response test(const ratl::rest::Request& request) {
        return {{}, 200};
    }
};
TEST_CASE("RestAPITest") {

    SECTION("Bad URIs give 404") {

        ratl::rest::RestAPI api{};

        const auto response = api.process({"/some/bad/uri", "POST", ""});

        CHECK(response.content == ratl::json{});
        CHECK(response.httpCode == 404);
    }

    SECTION("Routes without the specified method must give 405") {

        std::unique_ptr<ratl::rest::Router> router{new ratl::rest::Router{}};
        router->route("/test", "GET", [](const ratl::rest::Request &request) -> ratl::rest::Response {
            return {{}, 200};
        });

        ratl::rest::RestAPI api{};
        api.use(std::move(router));

        const auto response = api.process({"/test", "POST", ""});

        CHECK(response.content == ratl::json{});
        CHECK(response.httpCode == 405);
    }

    SECTION("Possibility to configure routers for RestAPI") {

        std::unique_ptr<ratl::rest::Router> router{new TestRouter{}};
        ratl::rest::RestAPI api{};
        api.use(std::move(router));

        const auto response = api.process({"/test", "GET", ""});

        CHECK(response.content == ratl::json{});
        CHECK(response.httpCode == 200);

    }

    SECTION("Possibility to accept parameters in URL Resource Path") {

        std::unique_ptr<ratl::rest::Router> router{new ratl::rest::Router{}};
        router->route("/test/<id>", "GET", [](const ratl::rest::Request &request) -> ratl::rest::Response {
            return {{}, 200};
        });

        ratl::rest::RestAPI api{};
        api.use(std::move(router));

        const auto response = api.process({"/test/123", "GET", ""});

        CHECK(response.content == ratl::json{});
        CHECK(response.httpCode == 200);
    }

    SECTION("Possibility to retrieve parameters in URL Resource Path from the request") {

        std::unique_ptr<ratl::rest::Router> router{new ratl::rest::Router{}};
        const std::string paramId = "123";

        router->route("/test/<id>", "GET", [&paramId](const ratl::rest::Request &request) -> ratl::rest::Response {
            const auto& id = request.getParameter<std::string>("id");
            CHECK_FALSE(id.empty());
            CHECK(id == paramId);

            return {{}, 200};
        });

        ratl::rest::RestAPI api{};
        api.use(std::move(router));

        const auto response = api.process({"/test/" + paramId, "GET", ""});

        CHECK(response.content == ratl::json{});
        CHECK(response.httpCode == 200);
    }
/*
    SECTION("Router Matches") {

        const auto defaultHandler = [](const ratl::rest::Request &request) -> ratl::rest::Response {
            return {{}, 200};
        };

        const auto argHandler = [](const std::string& name, const std::string& value) {
            return [=](const ratl::rest::Request &request) -> ratl::rest::Response {
                const auto& param = request.getParameter<std::string>(name);
                CHECK_FALSE(param.empty());
                CHECK(param == value);
            };
        };

        std::unique_ptr<ratl::rest::Router> router{new ratl::rest::Router{}};
        router->route("/", "GET", defaultHandler);
        router->route("/somepath", "GET", defaultHandler);
        router->route("/some/path", "GET", defaultHandler);
        router->route("/some/deep/path", "GET", defaultHandler);
        router->route("/<simplearg>", "GET", argHandler("simplearg", "simplevalue"));

        ratl::rest::RestAPI api{};
        api.use(std::move(router));

        SECTION("Match /") {
            const auto response = api.process({"/", "GET", ""});

            CHECK(response.content == ratl::json{});
            CHECK(response.httpCode == 200);
        }

        SECTION("Match /somepath") {
            const auto response = api.process({"/somepath", "GET", ""});

            CHECK(response.content == ratl::json{});
            CHECK(response.httpCode == 200);
        }

        SECTION("Match /some/path") {
            const auto response = api.process({"/some/path", "GET", ""});

            CHECK(response.content == ratl::json{});
            CHECK(response.httpCode == 200);
        }

        SECTION("Match /some/deep/path") {
            const auto response = api.process({"/some/deep/path", "GET", ""});

            CHECK(response.content == ratl::json{});
            CHECK(response.httpCode == 200);
        }

        SECTION("Match /<simplearg>") {
            const auto response = api.process({"/simplevalue", "GET", ""});

            CHECK(response.content == ratl::json{});
            CHECK(response.httpCode == 200);
        }

        SECTION("Match /simple/<arg>") {
            CHECK(false);
        }

        SECTION("Match /multiple/<simple>/<args>") {
            CHECK(false);
        }

        SECTION("Match /typed/<int:arg>") {
            CHECK(false);
        }

        SECTION("Match /typed/<float:arg>") {
            CHECK(false);
        }

        SECTION("Match /typed/<path:arg>") {
            CHECK(false);
        }

        SECTION("Match /typed/<path:arg>/inthemiddle") {
            CHECK(false);
        }

        SECTION("Match /typed/<uuid:arg>") {
            CHECK(false);
        }

    }
    */
}