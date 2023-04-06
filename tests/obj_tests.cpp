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

TEST_CASE("Modifier", tag)
{
    json5pp::value v = json5pp::object();
    CHECK(v.is_object());

    SECTION("adds a propery")
    {
        CHECK(v["name"].is_null());
        v["name"] = 1;
        CHECK(v["name"].is_number());
        CHECK(v["name"].get<int>() == 1);
        v.clear();
        CHECK(v.empty());
    }

    SECTION("remove a property")
    {
        v["age"] = 100;

        CHECK(v.contains("age"));
        v.erase("age");
        // object does not have the property.
        // in javascript, it means v.age === undefined
        CHECK(!v.contains("age"));
        CHECK(v.empty());

        // operator[] adds a new property with a null value.
        // in javascript, it means v.age === null
        CHECK(v["age"].is_null());
    }
}