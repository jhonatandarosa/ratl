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
}