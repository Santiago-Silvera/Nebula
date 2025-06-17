#include "vk_instance.h"

#include "core.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "vk_core.h"
#include "vk_debug.h"

b8 check_validation_layer_support(const char **validationLayers, u32 validationLayerCount);
const char **get_required_extensions(u32 validationLayerCount, u32 *outExtensionCount);

VkInstance create_vulkan_instance(const char **validationLayers, u32 validationLayerCount) {
    if (enableValidationLayers && !check_validation_layer_support(validationLayers, validationLayerCount)) {
        NFATAL("Validation layers requested, but not available.\n")
        exit(EXIT_FAILURE);
    }

    VkInstance instance;

    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "NEBULA Engine Application",
        .applicationVersion = VK_MAKE_VERSION(0, 0, 1),
        .pEngineName = "NEBULA Engine",
        .engineVersion = VK_MAKE_VERSION(0, 1, 1),
        .apiVersion = VK_API_VERSION_1_2
    };

    u32 extensionCount;
    const char **extensions = get_required_extensions(validationLayerCount, &extensionCount);

    VkInstanceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = extensionCount,
        .ppEnabledExtensionNames = extensions,
    };
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = validationLayerCount;
        createInfo.ppEnabledLayerNames = validationLayers;
        populateDebugMessengerCreateInfo(&debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *) &debugCreateInfo;
    }

    if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
        NFATAL("Failed to create Vulkan instance.\n")
        free(extensions);
        exit(EXIT_FAILURE);
    }

    free(extensions);
    return instance;
}

b8 check_validation_layer_support(const char **validationLayers, u32 validationLayerCount) {
    u32 layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);

    VkLayerProperties *availableLayers = malloc(layerCount * sizeof(VkLayerProperties));
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);

    NDEBUG("validationLayerCount: %d\n", validationLayerCount)
    NDEBUG("layerCount: %d\n", layerCount)
    for (u32 i = 0; i < validationLayerCount; i++) {
        const char *layerName = validationLayers[i];
        b8 layerFound = false;

        for (u32 j = 0; j < layerCount; j++) {
            if (strcmp(layerName, availableLayers[j].layerName) == 0) {
                NDEBUG("Validation layer found: %s\n", layerName)
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            free(availableLayers);
            return false;
        }
    }
    free(availableLayers);

    return true;
}

/**
 * @brief Get the required extensions as an array of char *
 * 
 * @param validationLayerCount 
 * @param outExtensionCount pointer to the number of extensions. Will be set by function
 * @return const char** Array of required extensions
 */
const char **get_required_extensions(u32 validationLayerCount, u32 *outExtensionCount) {
    u32 glfwExtensionCount = 0;
    const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    u32 totalExtensionCount = glfwExtensionCount;
    if (enableValidationLayers) {
        totalExtensionCount += validationLayerCount;
    }

    const char **extensions = malloc(totalExtensionCount * sizeof(const char *));
    memcpy(extensions, glfwExtensions, glfwExtensionCount * sizeof(const char *));
    if (enableValidationLayers) {
        extensions[glfwExtensionCount] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    }

    if (outExtensionCount) {
        *outExtensionCount = totalExtensionCount;
    }

    return extensions;
}
