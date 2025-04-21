#pragma once

#define cLLM_VERSION_MAJOR 0
#define cLLM_VERSION_MINOR 1
#define cLLM_VERSION_PATCH 0
#define cLLM_VERSION_STRING "0.1.0"
#define cLLM_VERSION (cLLM_VERSION_MAJOR * 10000 + cLLM_VERSION_MINOR * 100 + cLLM_VERSION_PATCH)



#ifdef _WIN32
#ifdef cLLM_EXPORTS
#define CLLM_API __declspec(dllexport)
#else
#define CLLM_API __declspec(dllimport)
#endif
#else
#define CLLM_API __attribute__((visibility("default")))
#endif
