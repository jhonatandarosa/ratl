#include <catch.hpp>

#include <ratl/router/RTrie.h>
#include <ratl/router/RTrieException.h>

using ratl::router::RTrie;
using ratl::router::RTrieException;

namespace Catch {
    template<>
    struct StringMaker<ratl::router::RTrieMatch> {
        static std::string convert( ratl::router::RTrieMatch const& value ) {
            return std::string("RTrieMatch{") + (value ? "true" : "false") +"}";
        }
    };
}


TEST_CASE( "RTrieTest" ) {

    RTrie rt;

    SECTION("Empty paths should throw exceptions") {
        CHECK_THROWS_AS(rt.insertPath(""), RTrieException);
    }

    SECTION("Invalid paths should throw exceptions") {
        CHECK_THROWS(rt.insertPath(" "));
        CHECK_THROWS(rt.insertPath("312312"));
        CHECK_THROWS(rt.insertPath("adasda"));
        CHECK_THROWS(rt.insertPath("haud12312"));
        CHECK_THROWS(rt.insertPath("//"));
    }

    SECTION("Match with empty trie should return no match") {
        CHECK_FALSE(rt.match("/"));
    }

    SECTION("Allow to insert root route") {
        CHECK_NOTHROW(rt.insertPath("/"));
    }

    SECTION("Match root route") {
        rt.insertPath("/");

        CHECK(rt.match("/"));
    }

    SECTION("Match path not in trie should return invalid match") {
        rt.insertPath("/");

        CHECK_FALSE(rt.match("/simple"));
    }

    SECTION("Allow to insert simple route") {
        CHECK_NOTHROW(rt.insertPath("/"));
    }

    SECTION("Match a simple route") {
        rt.insertPath("/simple");

        CHECK(rt.match("/simple"));
    }

    SECTION("Trailing '/' should make no difference") {
        rt.insertPath("/simple");
        rt.insertPath("/simple/");

        auto ctx1 = rt.match("/simple");
        CHECK(ctx1);

        auto ctx2 = rt.match("/simple/");
        CHECK(ctx2);

        CHECK(ctx1 == ctx2);
    }

    SECTION("Two simple routes must be on different contexts") {
        rt.insertPath("/simple1");
        rt.insertPath("/simple2");

        auto ctx1 = rt.match("/simple1");
        CHECK(ctx1);

        auto ctx2 = rt.match("/simple2");
        CHECK(ctx2);

        CHECK(ctx1 != ctx2);
    }

    SECTION("Two matchs of the same route must be on the same context") {
        rt.insertPath("/simple");

        auto ctx1 = rt.match("/simple");
        CHECK(ctx1);

        auto ctx2 = rt.match("/simple");
        CHECK(ctx2);

        CHECK(ctx1 == ctx2);
    }

    SECTION("Match a route with multiple components") {
        rt.insertPath("/a");
        rt.insertPath("/a/b");
        rt.insertPath("/a/c");
        rt.insertPath("/a/d");
        rt.insertPath("/a/b/c");
        rt.insertPath("/a/b/c/d");
        rt.insertPath("/a/b/c/d/e");
        rt.insertPath("/a/b/c/d/e/f");
        rt.insertPath("/a/b/c/d/e/f/g");
        rt.insertPath("/a/b/c/d/e/f/g/h");
        rt.insertPath("/a/b/c/d/e/f/g/h/i");
        rt.insertPath("/a/b/c/d/e/f/g/h/i/j");
        rt.insertPath("/a/b/c/d/e/f/g/h/i/j/k");
        rt.insertPath("/a/b/c/d/e/f/g/h/i/j/k/l");

        CHECK(rt.match("/a"));
        CHECK(rt.match("/a/b"));
        CHECK(rt.match("/a/c"));
        CHECK(rt.match("/a/d"));
        CHECK(rt.match("/a/b/c"));
        CHECK(rt.match("/a/b/c/d"));
        CHECK(rt.match("/a/b/c/d/e"));
        CHECK(rt.match("/a/b/c/d/e/f"));
        CHECK(rt.match("/a/b/c/d/e/f/g"));
        CHECK(rt.match("/a/b/c/d/e/f/g/h"));
        CHECK(rt.match("/a/b/c/d/e/f/g/h/i"));
        CHECK(rt.match("/a/b/c/d/e/f/g/h/i/j"));
        CHECK(rt.match("/a/b/c/d/e/f/g/h/i/j/k"));
        CHECK(rt.match("/a/b/c/d/e/f/g/h/i/j/k/l"));
    }

    SECTION("A RTrieMatch of a route without parameters must have no parameters inside") {
        rt.insertPath("/noargs");

        auto ctx = rt.match("/noargs");
        CHECK(ctx);

        CHECK(ctx.params().empty());
    }

    SECTION("Match a route with a simple argument") {
        rt.insertPath("/simple/<arg>");

        CHECK_FALSE(rt.match("/simple"));
        CHECK_FALSE(rt.match("/simple/"));

        auto ctx = rt.match("/simple/value");
        CHECK(ctx);

        REQUIRE_FALSE(ctx.params().empty());

        auto value = ctx.params().at("arg");
        CHECK(value == "value");
    }

    SECTION("Match a route with a simple argument in the middle") {
        rt.insertPath("/simple/<arg>/inthemiddle");

        CHECK_FALSE(rt.match("/simple"));
        CHECK_FALSE(rt.match("/simple/"));
        CHECK_FALSE(rt.match("/simple/value"));

        auto ctx = rt.match("/simple/value/inthemiddle");
        CHECK(ctx);

        REQUIRE_FALSE(ctx.params().empty());

        auto value = ctx.params().at("arg");
        CHECK(value == "value");
    }

    SECTION("Prefer routes with least arguments") {
        rt.insertPath("/simple/<arg1>/<arg2>");
        rt.insertPath("/simple/<arg>/least_arguments");

        CHECK_FALSE(rt.match("/simple"));
        CHECK_FALSE(rt.match("/simple/"));
        CHECK_FALSE(rt.match("/simple/value"));

        auto ctxLeastArguments = rt.match("/simple/value/least_arguments");
        CHECK(ctxLeastArguments);

        auto value = ctxLeastArguments.params().at("arg");
        CHECK(value == "value");

        auto ctxTwoArguments = rt.match("/simple/value/value2");
        CHECK(ctxTwoArguments);

        auto v1 = ctxTwoArguments.params().at("arg1");
        CHECK(v1 == "value");
        auto v2 = ctxTwoArguments.params().at("arg2");
        CHECK(v2 == "value2");

        CHECK(ctxLeastArguments != ctxTwoArguments);
    }

//    SECTION("Match /simple/<arg>") {
//        CHECK(false);
//    }
//
//    SECTION("Match /multiple/<simple>/<args>") {
//        CHECK(false);
//    }
//
//    SECTION("Match /typed/<int:arg>") {
//        CHECK(false);
//    }
//
//    SECTION("Match /typed/<float:arg>") {
//        CHECK(false);
//    }
//
//    SECTION("Match /typed/<path:arg>") {
//        CHECK(false);
//    }
//
//    SECTION("Match /typed/<path:arg>/inthemiddle") {
//        CHECK(false);
//    }
//
//    SECTION("Match /typed/<uuid:arg>") {
//        CHECK(false);
//    }
}