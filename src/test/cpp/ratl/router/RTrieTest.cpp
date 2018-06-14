#include <catch.hpp>

#include <ratl/router/RTrie.h>
#include <ratl/router/RTrieException.h>

using ratl::router::RTrie;
using ratl::router::RTrieException;

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
        auto node = rt.match("/");
        CHECK(node == nullptr);
    }

    SECTION("Allow to insert root route") {
        CHECK_NOTHROW(rt.insertPath("/"));
    }

    SECTION("Match root route") {
        rt.insertPath("/");

        auto node = rt.match("/");
        CHECK(node != nullptr);
    }

    SECTION("Match path not in trie should return nullptr") {
        rt.insertPath("/");

        auto node = rt.match("/simple");
        CHECK(node == nullptr);
    }

    SECTION("Allow to insert simple route") {
        CHECK_NOTHROW(rt.insertPath("/"));
    }

    SECTION("Match a simple route") {
        rt.insertPath("/simple");

        auto node = rt.match("/simple");
        CHECK(node != nullptr);
    }

    SECTION("Trailing '/' should make no difference") {
        rt.insertPath("/simple");
        rt.insertPath("/simple/");

        auto node1 = rt.match("/simple");
        CHECK(node1 != nullptr);

        auto node2 = rt.match("/simple/");
        CHECK(node2 != nullptr);

        CHECK(node1 == node2);
    }

    SECTION("Two simple routes must be on different nodes") {
        rt.insertPath("/simple1");
        rt.insertPath("/simple2");

        auto nodeSimple1 = rt.match("/simple1");
        CHECK(nodeSimple1 != nullptr);

        auto nodeSimple2 = rt.match("/simple2");
        CHECK(nodeSimple2 != nullptr);

        CHECK(nodeSimple1 != nodeSimple2);
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

        CHECK(rt.match("/a") != nullptr);
        CHECK(rt.match("/a/b") != nullptr);
        CHECK(rt.match("/a/c") != nullptr);
        CHECK(rt.match("/a/d") != nullptr);
        CHECK(rt.match("/a/b/c") != nullptr);
        CHECK(rt.match("/a/b/c/d") != nullptr);
        CHECK(rt.match("/a/b/c/d/e") != nullptr);
        CHECK(rt.match("/a/b/c/d/e/f") != nullptr);
        CHECK(rt.match("/a/b/c/d/e/f/g") != nullptr);
        CHECK(rt.match("/a/b/c/d/e/f/g/h") != nullptr);
        CHECK(rt.match("/a/b/c/d/e/f/g/h/i") != nullptr);
        CHECK(rt.match("/a/b/c/d/e/f/g/h/i/j") != nullptr);
        CHECK(rt.match("/a/b/c/d/e/f/g/h/i/j/k") != nullptr);
        CHECK(rt.match("/a/b/c/d/e/f/g/h/i/j/k/l") != nullptr);
    }

    SECTION("Match a route with a simple argument") {
        rt.insertPath("/simple/<arg>");

        CHECK(rt.match("/simple") == nullptr);
        CHECK(rt.match("/simple/") == nullptr);

        CHECK(rt.match("/simple/value") != nullptr);
    }

    SECTION("Match a route with a simple argument in the middle") {
        rt.insertPath("/simple/<arg>/inthemiddle");

        CHECK(rt.match("/simple") == nullptr);
        CHECK(rt.match("/simple/") == nullptr);
        CHECK(rt.match("/simple/value") == nullptr);

        CHECK(rt.match("/simple/value/inthemiddle") != nullptr);
    }

    SECTION("Prefer routes with least arguments") {
        rt.insertPath("/simple/<arg1>/<arg2>");
        rt.insertPath("/simple/<arg>/least_arguments");

        CHECK(rt.match("/simple") == nullptr);
        CHECK(rt.match("/simple/") == nullptr);
        CHECK(rt.match("/simple/value") == nullptr);

        auto nodeLeastArguments = rt.match("/simple/value/least_arguments");
        CHECK(nodeLeastArguments != nullptr);

        auto nodeTwoArguments = rt.match("/simple/value/value2");
        CHECK(nodeTwoArguments != nullptr);

        CHECK(nodeLeastArguments != nodeTwoArguments);
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