#include "json5pp.hpp"

static bool verify(const json5pp::value& value)
{
  return value.as_string() == "a\bcde\fg_\"\t\\test\nbar\r/d";
}
