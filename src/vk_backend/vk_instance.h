#pragma once

#include "core.h"
#include <vulkan/vulkan.h>

#ifdef DEBUG
static const u8 enableValidationLayers = true;
#else
static const u8 enableValidationLayers = false;
#endif

VkInstance create_vulkan_instance(const char **validationLayers, u32 validationLayerCount);
