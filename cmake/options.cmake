
option(CLLLM_BUILD_TESTS "Enable unit tests.Default is OFF" OFF)
if(CLLLM_BUILD_TESTS)
    add_definitions(-DCLLLM_BUILD_TESTS=1)
endif()
option(CLLM_LOGGING "Enable logging is OFF" OFF)