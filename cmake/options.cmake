option(NOVA_LLM_BUILD_TESTS "Enable unit tests.Default is OFF" OFF)
if(NOVA_LLM_BUILD_TESTS)
    add_definitions(-DNOVA_LLM_BUILD_TESTS=1)
endif()
option(NOVA_LLM_ENABLE_LOGGING "Enable logging is OFF" OFF)
option(NOVA_LLM_INTEGRATE_TVM "Integrate TVM library" OFF) #TODO