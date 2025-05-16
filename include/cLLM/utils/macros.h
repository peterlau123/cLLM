#pragma once

#define cLLM_VERSION_MAJOR 0
#define cLLM_VERSION_MINOR 1
#define cLLM_VERSION_PATCH 0
#define cLLM_VERSION_STRING "0.1.0"
#define cLLM_VERSION (cLLM_VERSION_MAJOR * 10000 + cLLM_VERSION_MINOR * 100 + cLLM_VERSION_PATCH)

#if defined(_MSC_VER)
#define CLLM_API __declspec(dllexport)
#elif defined(__GNUC__)
#define CLLM_API __attribute__((visibility("default")))
#else
#define CLLM_API
#endif

#define _IN
#define _OUT
#define _INOUT