#include <catch2/catch.hpp>

#include <json5pp/json5pp.hpp>

namespace {
const auto tag = "[array]";
}

TEST_CASE("array-creator", tag)
{
    SECTION("helper method")
    {
        json5pp::value ar = json5pp::array();
        CHECK(ar.is_array());
    }
    SECTION("explicit initialiser list")
    {
        json5pp::value ar{1, 2};
        CHECK(ar.is_array());
    }
}

TEST_CASE("array-modifier", tag)
{
    json5pp::value v = json5pp::array();
    CHECK(v.is_array());
    CHECK(v.size() == 0);

    CHECK_THROWS(v.at(1));
    CHECK_THROWS(v[1]);

    v.append(1).append("abc");
    CHECK(v.size() == 2);
    CHECK(v[0] == 1);
    CHECK(v[1] == "abc");

    v.erase(0);
    CHECK(v.size() == 1);
    CHECK(v[0] == "abc");

    v.clear();
    CHECK(v.empty());
}