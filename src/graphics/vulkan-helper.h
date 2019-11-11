#ifndef VULKAN_HELPER_H
#define VULKAN_HELPER_H

#include <fstream>
#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "../utils/log.h"

namespace VulkanTest::Graphics {

	bool checkAvailableVulkanExtensions(std::vector<VkExtensionProperties>& extensionsProperties);
	bool checkIfRequiredExtensionsArePresent(const std::vector<const char*>& requiredExtensions, const std::vector<VkExtensionProperties>& availableExtensions);
	bool isExtensionSupported(const std::vector<VkExtensionProperties>& availableExtensions, const std::string& extension);
	bool createVulkanInstance(VkInstance& instance, const std::vector<const char*>& requiredExtensions);
	bool readRequiredExtension(const std::string& filepath, std::vector<std::string>& requiredExtensions);
	bool enumeratePhysicalDevices(VkInstance& instance, std::vector<VkPhysicalDevice>& availableDevices);
	bool enumeratePhysicalDeviceExtensions(const VkPhysicalDevice& device, std::vector<VkExtensionProperties>& extensionProperties);
}

#endif
