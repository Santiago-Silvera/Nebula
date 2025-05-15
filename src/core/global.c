#include "global.h"
#include <stdlib.h>
#include "window.h"
#include "core.h"

EngineContext initEngine() {
  EngineContext ctx;
  ctx.vk_ctx = (VulkanContext*)malloc(sizeof(VulkanContext));
  if (!ctx.vk_ctx) {
    NFATAL("Failed to allocate VulkanContext.\n")
    exit(EXIT_FAILURE);
  }

  // TODO: add a pointer to some logger maybe??
  if (!init_logger()) exit(EXIT_FAILURE);

  if (!initWindow(&ctx)) {
    NFATAL("Failed to initialize window.\n")
    exit(EXIT_FAILURE);
  }

  if (!initVulkan(ctx.vk_ctx)) {
    NFATAL("Failed to initialize Vulkan.\n")
    exit(EXIT_FAILURE);
  }

  return ctx;
}

void mainLoop(EngineContext ctx) {
  while (!glfwWindowShouldClose(ctx.window)) {
    glfwPollEvents();
  }
}

void cleanupEngine(EngineContext ctx) {
  NINFO("Cleaning up engine.\n")
  cleanupWindow(ctx.window);
  if (ctx.vk_ctx) {
    cleanupVulkan(ctx.vk_ctx);
    free(ctx.vk_ctx);
    ctx.vk_ctx = NULL;
  }
  end_logger();
}