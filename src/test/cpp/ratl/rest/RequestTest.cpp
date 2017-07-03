#include <catch.hpp>

#include <ratl/json.h>
#include <ratl/rest/Request.h>
#include <ratl/rest/Resource.h>
namespace RequestTest {
    ratl::rest::ResourceFunction default_handler = [](const ratl::rest::Request &request) -> ratl::rest::Response {
        return {{}, 200};
    };
}

TEST_CASE( "RequestTest" ) {

    SECTION("Requests without payload should be empty") {

        ratl::rest::Request request{"/some/uri", "GET", {}};
        CHECK(request.empty());
    }

    SECTION("try to get parameter from a request with no parameters should throw logic_error") {

        ratl::rest::Request request{"/some/uri", "GET", {}};
        CHECK_THROWS_AS(request.getParameter<std::string>("id"), std::logic_error);
    }

    SECTION("Request with name uri params should be possible to retrieve those params") {

        const std::string uri = "/some/uri/123";
        ratl::rest::Resource resource{"/some/uri/<id>", "GET", RequestTest::default_handler};
        CHECK(resource.match(uri));
        ratl::rest::Request request{uri, resource.method, {}};
        request.init(resource);
        CHECK(request.getParameter<std::string>("id") == "123");
    }

    SECTION("Requests on '/' must work") {

        const std::string uri = "/";
        ratl::rest::Resource resource{"/", "GET", RequestTest::default_handler};
        CHECK(resource.match(uri));
    }

    SECTION("Parametrized requests on '/' must work") {

        const std::string uri = "/123";
        ratl::rest::Resource resource{"/<id>", "GET", RequestTest::default_handler};
        CHECK(resource.match(uri));
        ratl::rest::Request request{uri, resource.method, {}};
        request.init(resource);
        CHECK(request.getParameter<std::string>("id") == "123");
    }

}