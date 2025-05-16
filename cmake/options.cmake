
option(CLLM_BUILD_TESTS "Enable unit tests.Default is OFF" OFF)
if(CLLM_BUILD_TESTS)
    add_definitions(-DCLLM_BUILD_TESTS=1)
endif()
option(CLLM_ENABLE_LOGGING "Enable logging is OFF" OFF)