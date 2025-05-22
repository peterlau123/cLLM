#include "NovaLLM/cLLM-cpp.h"

namespace nova_llm {

Engine::Engine() = default;

Engine::~Engine() = default;

bool Engine::init() { return true; }

bool Engine::isAvailable() const { return true; }

DeviceType Engine::type() const { return DeviceType::CPU; }

}  // namespace nova_llm