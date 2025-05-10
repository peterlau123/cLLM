# 设置构建目录
BUILD_DIR := ../cllm_build

# 支持并行构建
ifneq (,$(filter -j%,$(MAKEFLAGS)))
JOBS := $(patsubst -j%,%,$(filter -j%,$(MAKEFLAGS)))
BUILD_FLAGS := -j$(JOBS)
else
BUILD_FLAGS :=
endif

.PHONY: all build clear install docs

# 默认目标
all: build
	@cmake --build $(BUILD_DIR) $(BUILD_FLAGS)

# 配置构建
build:
	@cmake -B $(BUILD_DIR) -S .

# 清理构建目录
clear:
	@rm -rf $(BUILD_DIR)

# 安装目标
install: build
	@cmake --build $(BUILD_DIR) --target install $(BUILD_FLAGS)

# 生成文档
docs: build
	@cmake --build $(BUILD_DIR) --target docs