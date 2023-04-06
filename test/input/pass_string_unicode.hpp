#include "json5pp.hpp"

static bool verify(const json5pp::value& value)
{
    return value.as_string() == (const char*)u8"fooあ123";
}
