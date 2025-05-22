#pragma once

#include "utils/macros.h"

typedef void* EngineHandle;

bool NOVA_LLM_API init_engine();

bool NOVA_LLM_API load_model(EngineHandle hdl, const char* model_path);
