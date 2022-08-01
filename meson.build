project('json5cpp', ['cpp'], meson_version: '>=0.58.0', version: files('VERSION'), default_options : ['cpp_std=c++17', 'werror=true'])

# stop after 1 errors
if meson.get_compiler('cpp').get_id() == 'gcc'
    add_global_arguments(['-fmax-errors=1', '-fdiagnostics-show-option'], language: ['cpp']) 
endif

# head-only
json5cpp_dep = declare_dependency(include_directories: './include')

# unit tests
if get_option('build_test')
    subdir('tests')
endif

