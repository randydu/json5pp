#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <array>
#include <string>

#include <json5pp.hpp>

namespace {
const auto tag = "[basic]";
}

TEST_CASE("null", tag)
{
    constexpr auto null_str = "null";

    SECTION("stringify")
    {
        json5pp::value v;
        CHECK(v.is_null());
        CHECK(json5pp::stringify(v) == null_str);
        CHECK(json5pp::stringify5(v) == null_str);
    }

    SECTION("parse")
    {
        CHECK(json5pp::parse(null_str).is_null());
        CHECK(json5pp::parse5(null_str).is_null());
    }
}

TEST_CASE("boolean", tag)
{
    SECTION("stringify")
    {
        {
            json5pp::value v(true);
            CHECK(v.is_boolean());
            CHECK(json5pp::stringify(v) == "true");
        }
        {
            json5pp::value v(false);
            CHECK(v.is_boolean());
            CHECK(json5pp::stringify5(v) == "false");
        }
    }

    SECTION("parse")
    {
        {
            constexpr auto s = "true";
            {
                auto v = json5pp::parse(s);
                CHECK(v.is_boolean());
                CHECK(v.as_boolean());
            }
            {
                auto v = json5pp::parse5(s);
                CHECK(v.is_boolean());
                CHECK(v.as_boolean());
            }
        }
        {
            constexpr auto s = "false";
            {
                auto v = json5pp::parse(s);
                CHECK(v.is_boolean());
                CHECK(!v.as_boolean());
            }
            {
                auto v = json5pp::parse5(s);
                CHECK(v.is_boolean());
                CHECK(!v.as_boolean());
            }
        }
    }
}