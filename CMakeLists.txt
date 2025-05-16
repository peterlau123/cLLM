cmake_minimum_required(VERSION 3.14...3.22)

# ---- Project ----

# Note: update this to your new project's name and version
project(
  cLLM
  VERSION 0.1.0
  LANGUAGES CXX
  HOMEPAGE_URL  "https://github.com/peterlau123/cLLM"
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Set CMake options ----


# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

include(cmake/options.cmake)

include(cmake/CPMDependency.cmake)

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# -- build settings ---
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()
# ---- Create library ----
# 查找 Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND)
    # 添加文档生成目标
    add_custom_target(docs
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM
    )
endif()

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
# target: add_library(${PROJECT_NAME} INTERFACE)
if(CLLM_BUILD_TESTS)
    set(CLLM_TEST_TARGET ${PROJECT_NAME}_test )
    add_executable(${CLLM_TEST_TARGET}
            ${sources}
    )
endif ()

if(NOT CLLM_BUILD_TESTS)
    list(FILTER sources EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/source/.*_test\\.cpp$")
endif ()
add_library(${PROJECT_NAME} SHARED ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
set(DEPENDENCY_LIST fmt::fmt)
if(CLLM_ENABLE_LOGGING)
  LIST(APPEND DEPENDENCY_LIST spdlog::spdlog)
endif(
  CLLM_ENABLE_LOGGING
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${DEPENDENCY_LIST} )
if(CLLM_BUILD_TESTS)
  LIST(APPEND DEPENDENCY_LIST GTest::gtest GTest::gmock)
  target_link_libraries(${CLLM_TEST_TARGET} PRIVATE ${PROJECT_NAME})
endif()

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

# 设置默认安装路径
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH "默认安装路径" FORCE)
    message(STATUS "设置安装路径为: ${CMAKE_INSTALL_PREFIX}")
endif()

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
  DEPENDENCIES "fmt 10.2.1;GTest 1.12.1;spdlog 1.12.0" # 这里添加你需要的依赖项
)
