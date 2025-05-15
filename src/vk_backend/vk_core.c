#include "vk_core.h"
#include "vk_debug.h"
#include "vk_instance.h"
#include "vk_device.h"
#include "types.h"

b8 initVulkan(VulkanContext *ctx) {
    VkInstance instance;
    VkDebugUtilsMessengerEXT debug_messenger;
    const char *validationLayers[] = {
        "VK_LAYER_KHRONOS_validation"
    };
    u32 validationLayerCount = sizeof(validationLayers) / sizeof(validationLayers[0]);

    instance = create_vulkan_instance(validationLayers, validationLayerCount);
    if (instance == VK_NULL_HANDLE || instance == NULL) {
        NFATAL("Failed to create Vulkan instance.\n")
        return false;
    }

    setupDebugMessenger(instance, &debug_messenger);
    ctx->vk_instance = instance;
    ctx->vk_debug_messenger = debug_messenger;
    pick_physical_device(ctx);
    return true;
}

void cleanupVulkan(VulkanContext *ctx) {
    if (!ctx) return;
    NINFO("Cleaning up Vulkan.\n")
    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(ctx->vk_instance, ctx->vk_debug_messenger, NULL);
    }
    vkDestroyInstance(ctx->vk_instance, NULL);
}