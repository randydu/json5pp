# Change Log

## v3.1.0

- adds type conversion template function: v.to<T>();
- adds implicit type conversion: (T)v;
- adds try_get(T&)/try_get(F f), get_or(def_val);
  simplify reading value from possible null content.

## v3.0.0

- Upgrades to C++20;
- Refactor json5cpp::value, replace union with std::variant, "type" field is removed;
- Remove unnecessary copy constructors/ copy assignment operators (default versions works fine);
- Adds int64_t support;
- Adds value operators; (==, >, >=, <, <=, >>, <<);
- Adds value::get<T, bool>();

## v2.3.0

- Adds meson-build scripts;
- Adds catch2-based unit tests;
- Improve stringify(...) to avoid possible local copy of parameters;
