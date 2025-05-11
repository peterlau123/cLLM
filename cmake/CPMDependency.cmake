# add fmt
CPMAddPackage(
  NAME fmt
  GIT_TAG 10.2.1
  GITHUB_REPOSITORY fmtlib/fmt
  OPTIONS "FMT_INSTALL YES" # create an installable target
)

if(CLLM_BUILD_TESTS)
  CPMAddPackage(
    NAME GTest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG main  # 或者使用特定版本，如 release-1.12.1
    VERSION 1.12.1
    OPTIONS
      "INSTALL_GTEST OFF"
      "BUILD_GMOCK ON"
  )
endif()


# 添加 spdlog
if(CLLM_ENABLE_LOGGING)
  CPMAddPackage(
      NAME spdlog
      GITHUB_REPOSITORY gabime/spdlog
      VERSION 1.12.0
      OPTIONS
          "SPDLOG_BUILD_SHARED OFF"
          "SPDLOG_BUILD_EXAMPLE OFF"
  )
endif()