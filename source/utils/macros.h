#pragma once
#include <stdexcept>
#include <string>

#ifdef NDEBUG
#  define ASSERT(condition, message) ((void)0)
#else
#  define ASSERT(condition, message)                                                          \
    do {                                                                                      \
      if (!(condition)) {                                                                     \
        throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " " \
                                 + message);                                                  \
      }                                                                                       \
    } while (0)
#endif