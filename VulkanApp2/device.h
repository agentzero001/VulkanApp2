#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "swapchain.h"
#include <optional>
#include <vector>
#include <set>

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

bool checkDeviceExtensionSupport(VkPhysicalDevice device);


struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete();
};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);


