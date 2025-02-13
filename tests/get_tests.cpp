#include <catch2/catch.hpp>
#include <json5pp/json5pp.hpp>

#include <iostream>

/**
 * @brief unit tests for value accessor
 *
 */

namespace {
const std::string tag = "[get]";
}

TEST_CASE("get_strict", tag)
{
    using namespace json5pp;

    value v = 1;
    CHECK(v.is_integer());
    CHECK(v.get_strict<int>() == 1);
    // CHECK_THROWS(v.get_strict<char>() == 1); //not compile because char is not built-in
    CHECK_THROWS(v.get_strict<long>() == 1);
}

TEST_CASE("get<T>()", tag)
{
    using namespace json5pp;

    {
        value v = 1;
        CHECK(v.get<char>() == 1);
        CHECK(v.get<int16_t>() == 1);
        CHECK(v.get<int>() == 1);
        CHECK(v.get<unsigned>() == 1);
        CHECK(v.get<long>() == 1);
        CHECK(v.get<float>() == 1);
        CHECK(v.get<double>() == 1);
        CHECK(v.get<std::string, true>() == "1"); // auto-conversion ON
        CHECK_THROWS(v.get<std::string>());       // auto-conversion OFF: str <-> number not allowed.
        CHECK(v.get<bool>() == true);
    }
    {
        value v = 0;
        CHECK(v.get<char>() == 0);
        CHECK(v.get<int16_t>() == 0);
        CHECK(v.get<int>() == 0);
        CHECK(v.get<unsigned>() == 0);
        CHECK(v.get<long>() == 0);
        CHECK(v.get<float>() == 0);
        CHECK(v.get<double>() == 0);
        CHECK_THROWS(v.get<std::string>());
        CHECK(v.get<std::string, true>() == "0");
        CHECK(v.get<bool>() == false);
    }
}


TEST_CASE("get(v)", tag)
{
    using namespace json5pp;

    value v = 1;
    {
        char x;
        v.get(x);
        CHECK(x == 1);
    }
    {
        bool x;
        v.get(x);
        CHECK(x);
    }
}

TEST_CASE(">>", tag)
{
    using namespace json5pp;

    SECTION("int")
    {
        value v = 1;
        {
            char x;
            v >> x;
            CHECK(x == 1);
        }
        {
            float x;
            v >> x;
            CHECK(x == 1.0);
        }
        {
            bool x;
            v >> x;
            CHECK(x);
        }
        {
            std::string x;
            CHECK_THROWS(v >> x);
        }
    }
    SECTION("string")
    {
        value v = "hello";
        {
            std::string x;
            v >> x;
            CHECK(x == "hello");
        }
        {
            bool x;
            CHECK_THROWS(v >> x);
        }
    }
}

TEST_CASE("<<", tag)
{
    SECTION("int")
    {
        json5pp::value v;
        v << 1;
        CHECK(v.is_integer());
        CHECK(v == 1);
        CHECK(1 == v);
        CHECK(v > 0);
        CHECK(v > 0.5);
        CHECK(v >= 0);
        CHECK(v < 2);
        CHECK(v <= 2);
        CHECK(0 < v);
        CHECK(0 <= v);

        {
            json5pp::value w = 2;
            CHECK_FALSE(v == w);
            CHECK(v != w);
            CHECK(v < w);
            CHECK(v <= w);
        }

        {
            int i;
            json5pp::value w(10);
            i << w;
            CHECK(i == 10);

            int j;
            w >> j;
            CHECK(j == 10);
        }
    }
}

TEST_CASE("null-get", tag)
{
    json5pp::value x(NULL);
    CHECK(x.is_integer());

    json5pp::value v;
    CHECK(v.is_null());
    CHECK(!v);
    CHECK_THROWS(v.get<std::string>());          // no auto conversion
    CHECK(v.get<std::string, true>() == "null"); // with auto conversion
    CHECK_THROWS(v.get<int, false>() == 0);
    CHECK_THROWS(v.get<int, true>() == 0);
    CHECK(v.get<void*>() == nullptr);
    CHECK(v.get<bool, true>() == false);
}

TEST_CASE("==", tag)
{
    SECTION("string")
    {
        using namespace std::string_literals;

        json5pp::value v("Hi");
        CHECK(v == "Hi"s);
        CHECK(v == "Hi");
        CHECK("Hi" == v);
        CHECK("Hi"s == v);
        CHECK("He"s != v);
        CHECK("He" != v);

        CHECK(json5pp::value("foo") == "foo");
    }
}

namespace {
bool verify_option(int a)
{
    return a < 10;
}
void show_option(int a)
{
    std::cout << a << std::endl;
}
} // namespace

TEST_CASE("try_get", tag)
{
    json5pp::value v(100), null;
    int i = 10;

    SECTION("try-get")
    {
        CHECK_FALSE(null.try_get(i));
        CHECK(i == 10); // unchanged

        CHECK(v.try_get(i));
        CHECK(i == 100); // changed

        CHECK(v.try_get<int>([](auto a) { //
            CHECK(a == 100);
        }));

        CHECK(v.try_get<int>(show_option));
        CHECK_FALSE(v.try_get<int>(verify_option));
        CHECK_FALSE(v.try_get<int>([](auto) { // Respect the processor result
            return false;
        }));

        CHECK(v.to<std::string>() == "100");
        CHECK_THROWS(v.get<std::string>() == "100");
        CHECK(v.get<std::string, true>() == "100");
    }

    SECTION("get_or")
    {
        CHECK(v.get_or(10) == 100);
        CHECK(null.get_or(10) == 10);
    }
}