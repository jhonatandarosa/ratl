#include <catch.hpp>

#include <ratl/json.h>
#include <ratl/rest/RestAPI.h>
#include <ratl/rest/Router.h>
#include <ratl/rest/Response.h>

class CustomRouter;

TEST_CASE( "RouterTest" ) {

    SECTION("Create a route with free function or lambda") {

        ratl::rest::Router router;
        CHECK(router.empty());

        router.route("/test", "GET", [](const ratl::rest::Request &request) -> ratl::rest::Response {
            return {{}, 200};
        });

        CHECK(!router.empty());
        CHECK(router.size() == 1);
    }

    SECTION("Create a route with member function of a extended Router") {

        class CustomRouter : public ratl::rest::Router {
        public:
            CustomRouter() {
                route<CustomRouter>("/test", "GET", &CustomRouter::test);
            }

            ratl::rest::Response test(const ratl::rest::Request& request) {
                return {{}, 200};
            }
        };

        CustomRouter router;

        CHECK(!router.empty());
        CHECK(router.size() == 1);
    }

}