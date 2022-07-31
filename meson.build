project('json5cpp', ['cpp'], meson_version: '>=0.58.0', version: files('VERSION'), default_options : ['cpp_std=c++11', 'werror=true'])

# head-only
json5cpp_dep = declare_dependency(include_directories: './include')

# unit tests
if get_option('build_test')
    subdir('tests')
endif

