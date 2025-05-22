cmake_minimum_required(VERSION 3.14...3.22)

project(NovaLLMTests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    CONAN_PKG::NovaLLM
    CONAN_PKG::gtest
    CONAN_PKG::fmt
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wpedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
  endif()
endif()

# ---- Enable testing ----

enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(${PROJECT_NAME} PRIVATE -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
endif()
