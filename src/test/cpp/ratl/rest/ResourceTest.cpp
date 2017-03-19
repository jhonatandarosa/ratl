#include <catch.hpp>

#include <ratl/json.h>
#include <ratl/rest/Resource.h>

namespace ResourceTest {
    ratl::rest::ResourceFunction default_handler = [](const ratl::rest::Request &request) -> ratl::rest::Response {
        return {{}, 200};
    };
}

TEST_CASE("ResourceTest") {

    using ratl::rest::Resource;

    SECTION("Create a route Resource without parameters") {

        Resource resource{"/test/resource", "GET", ResourceTest::default_handler};

        CHECK(resource.pattern == resource.uri);
    }

    SECTION("Create a route Resource with a simple parameter") {

        Resource resource{"/test/resource/<param>", "GET", ResourceTest::default_handler};

        CHECK(resource.match("/test/resource/123"));
        CHECK(resource.param(0) == "param");
    }

}