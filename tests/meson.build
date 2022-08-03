catch2_dep = dependency('catch2')

# speedup catch2 link time
catch2_speedup = static_library('catch2_speedup', 'main.cpp', dependencies: [ catch2_dep ])

srcs = ['basic_tests.cpp', 'obj_tests.cpp', 'get_tests.cpp',]

json5cpp_test = executable('json5cpp_test', srcs, dependencies: [ catch2_dep, json5cpp_dep], link_with: [catch2_speedup])

test('json5cpp-test', json5cpp_test)