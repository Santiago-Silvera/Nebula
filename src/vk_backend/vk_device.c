#include "core.h"
#include "vk_device.h"
#include <stdlib.h>

b8 is_device_suitable(VkPhysicalDevice device);

void pick_physical_device(VulkanContext *ctx) {
    u32 deviceCount = 0;
    vkEnumeratePhysicalDevices(ctx->vk_instance, &deviceCount, NULL);
    if (deviceCount == 0) {
        NFATAL("Failed to find GPUs with Vulkan support.\n")
        exit(EXIT_FAILURE);
    }

    VkPhysicalDevice *devices = malloc(deviceCount * sizeof(VkPhysicalDevice));
    if (!devices) {
        NFATAL("Failed to allocate memory for physical devices.\n");
        exit(EXIT_FAILURE);
    }

    vkEnumeratePhysicalDevices(ctx->vk_instance, &deviceCount, devices);

    ctx->physical_device = VK_NULL_HANDLE;

    for (int i = 0; i < deviceCount; i++) {
        if (is_device_suitable(devices[i])) {
            ctx->physical_device = devices[i];
            break;
        }
    }

    free(devices);

    if (ctx->physical_device == VK_NULL_HANDLE) {
        NFATAL("Failed to find a suitable GPU.\n")
        exit(EXIT_FAILURE);
    }
}

b8 is_device_suitable(VkPhysicalDevice device) {
    return true;
}