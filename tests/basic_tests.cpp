#include <catch2/catch.hpp>

#include <array>
#include <string>
#include <iostream>

#include <json5pp/json5pp.hpp>

namespace {
const auto tag = "[basic]";
}

TEST_CASE("null", tag)
{
    constexpr auto null_str = "null";

    SECTION("init empty value")
    {
        {
            json5pp::value v;
            CHECK(v.is_null());
        }
        {
            json5pp::value v{};
            CHECK(v.is_null());
        }
        {
            json5pp::value v = {};
            CHECK(v.is_null());
        }
        {
            json5pp::value v(nullptr);
            CHECK(v.is_null());
        }
        {
            json5pp::value v = nullptr;
            CHECK(v.is_null());
        }
    }

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
    SECTION("bool test")
    {
        {
            json5pp::value v{1, 2};
            CHECK(v.is_array());
            CHECK(v);
        }
        {
            auto v = json5pp::object({{"name", "xxx"}});
            CHECK(v.is_object());
            CHECK(v);
        }
    }
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

TEST_CASE("integer", tag)
{
    SECTION("int")
    {
        SECTION("constructor")
        {
            { // int&&
                auto v = json5pp::value(1);

                CHECK(v.is_integer());
                CHECK(v.as_integer() == 1);

                int x = v;
                CHECK(x == 1);
            }
            { // int&
                int x = 1;
                auto v = json5pp::value(x);

                CHECK(v.is_integer());
                CHECK(v.as_integer() == 1);
            }
        }
        SECTION("copy constructor")
        {
            {
                json5pp::value v{1}; // the same as: v = {1}
                CHECK(v.is_array());
                CHECK(v[0].as_integer() == 1);
            }
            {
                json5pp::value v(1);
                CHECK(v.is_integer());
                CHECK(v.as_integer() == 1);
            }
            {
                json5pp::value v = 1;
                CHECK(v.is_integer());
                CHECK(v.as_integer() == 1);
            }
            {
                int x = 1;
                json5pp::value v = x;
                CHECK(v.is_integer());
                CHECK(v.as_integer() == 1);
            }
            {
                json5pp::value x = 1;
                json5pp::value y = x;

                CHECK(x.is_integer());
                CHECK(x.as_integer() == 1);
                CHECK(y.is_integer());
                CHECK(y.as_integer() == 1);
            }
        }
        SECTION("copy operator")
        {
            json5pp::value x = 10;
            json5pp::value y;
            y = x;

            CHECK(x.is_integer());
            CHECK(x.as_integer() == 10);
            CHECK(y.is_integer());
            CHECK(y.as_integer() == 10);

            int i = x;
            CHECK(i == 10);

            int j;
            j = x;
            CHECK(j == 10);
        }
        SECTION("move operator")
        {
            json5pp::value x = 1;
            json5pp::value y;
            y = std::move(x);

            CHECK(x.is_integer()); // after move, the original value is not touched

            CHECK(y.is_integer());
            CHECK(y.as_integer() == 1);
        }
    }
    SECTION("int64_t")
    {
        int64_t x{1};
        auto v = json5pp::value(x);

        CHECK(v.is_integer());
        CHECK(v.as_integer() == 1);
    }

    SECTION("char")
    {
        json5pp::value v('a');

        CHECK(v.is_integer());
        CHECK(v.as_integer() == 'a');
    }
}

TEST_CASE("string", tag)
{
    SECTION("ascii")
    {
        std::string hello("Hello!");
        json5pp::value v(hello);

        CHECK(v.is_string());
        CHECK(v.as_string() == hello);
    }
    SECTION("utf8")
    {
        auto s = u8"fooあ123";
        json5pp::value v = s;

        CHECK(v.is_string());
        CHECK(v.as_string() == (const char*)s);
        CHECK(v == (const char*)s);
    }
    SECTION("=")
    {
        {
            std::string v = json5pp::value("Hello");
            CHECK(v == "Hello");
        }
        {
            json5pp::value x("Hello");
            std::string v;
            // compile error: ambugious overload for 'string::operator='
            // v = json5pp::value("Hello");
            v = x.as_string();
            CHECK(v == "Hello");

            bool b = x;
            CHECK_FALSE(b);

            b = x;
            CHECK_FALSE(b);

            x = "true";
            b = x;
            CHECK(b);
        }
    }
}

TEST_CASE("manipulators", tag)
{
    const auto x = json5pp::object({{"name", "Tom"}});
    std::string s1, s2;
    {
        std::stringstream stm;
        stm << json5pp::rule::space_indent<2>() << x;
        s1 = stm.str();
    }
    {
        std::stringstream stm;
        stm << x.stringify5(json5pp::rule::space_indent<2>());
        s2 = stm.str();
    }
    CHECK(s1 == s2);
}