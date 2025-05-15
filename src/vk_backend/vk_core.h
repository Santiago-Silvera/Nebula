#pragma once

#include <vulkan/vulkan.h>
#include "types.h"

typedef struct VulkanContext {
    VkInstance vk_instance;
    VkDebugUtilsMessengerEXT vk_debug_messenger;
    VkPhysicalDevice physical_device;
} VulkanContext;

/**
 * @brief Initalizes the Vulkan instance
 * 
 * @return b8 True if the instance was created successfully
 */
b8 initVulkan(VulkanContext* ctx);

/**
 * @brief Cleans up the Vulkan instance
 * 
 */
void cleanupVulkan(VulkanContext* ctx);