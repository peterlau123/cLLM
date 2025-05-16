cmake_minimum_required(VERSION 3.14...3.22)

# ===================== Project Options =====================
option(CLLM_ENABLE_LOGGING "Enable logging with spdlog" ON)
option(CLLM_BUILD_TESTS "Build tests with GTest" OFF)

# ===================== Project Info ========================
project(
  cLLM
  VERSION 0.1.0
  LANGUAGES CXX
  HOMEPAGE_URL  "https://github.com/peterlau123/cLLM"
)

# ===================== Conan Dependencies ==================
find_package(fmt REQUIRED)
if(CLLM_ENABLE_LOGGING)
  find_package(spdlog REQUIRED)
endif()
if(CLLM_BUILD_TESTS)
  find_package(GTest REQUIRED)
endif()

# ===================== Build Guards ========================
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please use a build directory.")
endif()

# ===================== CMake Options =======================
include(cmake/options.cmake)

# ===================== Source Files ========================
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# ===================== Documentation =======================
find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(docs
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating documentation with Doxygen"
    VERBATIM
  )
endif()

# ===================== Library & Executable ================
if(CLLM_BUILD_TESTS)
  set(CLLM_TEST_TARGET ${PROJECT_NAME}_test)
  add_executable(${CLLM_TEST_TARGET} ${sources})
endif()

if(NOT CLLM_BUILD_TESTS)
  list(FILTER sources EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/source/.*_test\\.cpp$")
endif()

add_library(${PROJECT_NAME} SHARED ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# ===================== Link Dependencies ===================
set(DEPENDENCY_LIST fmt::fmt)
if(CLLM_ENABLE_LOGGING)
  list(APPEND DEPENDENCY_LIST spdlog::spdlog)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE ${DEPENDENCY_LIST})

if(CLLM_BUILD_TESTS)
  list(APPEND DEPENDENCY_LIST GTest::gtest GTest::gmock)
  target_link_libraries(${CLLM_TEST_TARGET} PRIVATE ${DEPENDENCY_LIST})
endif()

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

# ===================== Install Targets =====================
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH "默认安装路径" FORCE)
  message(STATUS "设置安装路径为: ${CMAKE_INSTALL_PREFIX}")
endif()

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

install(FILES
    "${PROJECT_NAME}Config.cmake"
    "${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)

# ===================== Summary =============================
message(STATUS "\n==== cLLM Configuration Summary ====")
message(STATUS "  Logging:         ${CLLM_ENABLE_LOGGING}")
message(STATUS "  Build tests:     ${CLLM_BUILD_TESTS}")
message(STATUS "  Install prefix:  ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  C++ Standard:    17")
message(STATUS "  Conan deps:      fmt, spdlog, gtest")
message(STATUS "====================================\n")
