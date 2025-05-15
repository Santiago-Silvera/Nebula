#pragma once

#include <GLFW/glfw3.h>
#include "vk_core.h"

typedef struct EngineContext {
    GLFWwindow *window;
    VulkanContext *vk_ctx;
} EngineContext;

EngineContext initEngine();
void mainLoop(EngineContext ctx);
void cleanupEngine(EngineContext ctx);