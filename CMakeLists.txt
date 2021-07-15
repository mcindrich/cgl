cmake_minimum_required(VERSION 3.0.0)
project(cgl C)

include_directories(
    "lib"
    "deps"
)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

set(
    LIB_SOURCES
    "lib/cgl/object.c"
    "lib/cgl/error.c"
    "lib/cgl/shader.c"
    "lib/cgl/shader_program.c"
    "lib/cgl/vbo.c"
    "lib/cgl/ebo.c"
    "lib/cgl/vao.c"
)

add_library(
    ${CMAKE_PROJECT_NAME}
    ${LIB_SOURCES}
)
add_executable(
    cgl_learnopengl
    "test/cgl_learnopengl.c"
)
add_executable(
    learnopengl
    "test/learnopengl.c"
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE GLEW::GLEW glfw)
target_link_libraries(cgl_learnopengl ${CMAKE_PROJECT_NAME} GLEW::GLEW glfw)
target_link_libraries(learnopengl ${CMAKE_PROJECT_NAME} GLEW::GLEW glfw)
