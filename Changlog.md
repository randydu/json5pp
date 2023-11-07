# Change Log

## v3.4.1

FIX: adds missing assert header.

## v3.4.0

* adds array / object modifiers.
  reset(), clear(), size(), empty(), erase(), append(), [n | key] = v;

* reformat legacy tests;

## v3.3.0

adds std::optional<T> value getter;

```c++
std::optional<int> x;

json5pp::value jv;
jv.get(x);
assert(!x);
```


## v3.2.1

fix compile issue for string manipulators;


## v3.2.0

- change the include path, it is now recommended to include the header file like so:

```cpp
#include <json5pp/json5pp.h>
```

## v3.1.1

- fix Truthy test for object/array type;
- fix compile issue for VC2022;

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
