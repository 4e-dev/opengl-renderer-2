project(
  'opengl-renderer-2',
  'cpp',
  version: '0.1.0',
  default_options: [
    'cpp_std=c++23',
    'warning_level=3',
    'buildtype=debug',
  ],
)

include_dir = include_directories('include', 'test')

glfw_dep = declare_dependency(
  link_args: [
    '-L' + meson.current_source_dir() / 'lib/glfw',
    '-lglfw3',
  ],
  include_directories: include_dir,
)

opengl_dep = dependency('gl')
threads_dep = dependency('threads')

glad_lib = static_library(
  'glad',
  'src/glad.cpp',
  include_directories: include_dir,
)
glad_dep = declare_dependency(
  link_with: glad_lib,
  include_directories: include_dir,
)

exe = executable(
  'prog',
  [
    'src/main.cpp'
  ],
  dependencies: [
    glad_dep,
    glfw_dep,
    opengl_dep,
    threads_dep,
  ],
)

# test linear algebra library
test_linalg = executable(
  'test_linalg',
  [
    'test/main.cpp',
    'test/test_linalg.cpp',
  ],
  include_directories: include_dir,
)

test(
  'linear algebra',
  test_linalg,
)
