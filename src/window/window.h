#pragma once

#include <GLFW/glfw3.h>
#include "core.h"

static const u32 SCR_WIDTH = 800;
static const u32 SCR_HEIGHT = 600;

b8 initWindow(EngineContext *ctx);
void cleanupWindow(GLFWwindow *window);