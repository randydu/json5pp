srcs = ['basic_tests.cpp', 'obj_tests.cpp', ]

json5cpp_test = executable('json5cpp_test', srcs, dependencies: [ dependency('catch2'), json5cpp_dep])

test('json5cpp-test', json5cpp_test)