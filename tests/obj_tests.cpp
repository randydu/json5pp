#include <catch2/catch.hpp>

#include <json5pp/json5pp.hpp>

namespace {
const auto tag = "[obj]";
}

TEST_CASE("parse", tag)
{
    SECTION("json")
    {
        auto x = json5pp::parse("{\"foo\":[123,\"baz\"]}");
        CHECK(x.is_object());
        CHECK(x["foo"].is_array());
        CHECK(x["foo"][0].as_number() == 123);
        CHECK(x["foo"][1].as_string() == "baz");
    }

    SECTION("json5")
    {
        for (auto s : {
                 "{\"foo\":[123,\"baz\"]}",                                         // original json string
                 "{foo:[123,\"baz\"]}",                                             // keyword without quote
                 "{ foo: //this is comment\n[123,\"baz\"/*trailing comma-->*/,],}", // comment
                 R"({ //test comment
                    foo: [123, "baz" /* trailing comma-->*/,],
                    })",                                                            // comment
             }) {
            auto x = json5pp::parse5(s);
            CHECK(x.is_object());
            CHECK(x["foo"].is_array());
            CHECK(x["foo"][0].as_number() == 123);
            CHECK(x["foo"][1].as_string() == "baz");
        }
    }
}