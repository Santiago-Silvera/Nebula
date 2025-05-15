#pragma once

#include "core.h"
#include <vulkan/vulkan.h>

/**
 * @brief sets up the Debug manager for the instance
 * 
 * @param vk_instance 
 * @param vk_debug_messenger pointer to messenger to set
 */
void setupDebugMessenger(VkInstance vk_instance, VkDebugUtilsMessengerEXT* vk_debug_messenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT *createInfo);

VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData);