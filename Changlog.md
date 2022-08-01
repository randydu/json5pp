# Change Log

## v3.0.0

* Upgrades to C++20;
* Refactor json5cpp::value, replace union with std::variant, "type" field is removed;
* Remove unnecessary copy constructors/ copy assignment operators (default versions works fine);
* Adds int64_t support;

## v2.3.0

* Adds meson-build scripts;
* Adds catch2-based unit tests;
* Improve stringify(...) to avoid possible local copy of parameters;

