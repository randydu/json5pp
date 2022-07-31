project('json5cpp', ['cpp'], meson_version: '>=0.58.0', version: '2.2.0', default_options : ['cpp_std=c++17', 'werror=true'])

if get_option('build_test')
    subdir('tests')
endif

# head-only
json5cpp_dep = declare_dependency(include_directories: '.')
