#pragma once

#include "utils/macros.h"

typedef void* EngineHandle;

bool CLLM_API init_engine();

bool CLLM_API load_model(EngineHandle hdl, const char* model_path);
