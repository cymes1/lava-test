#ifndef TEST_AVAILABLE_VULKAN_EXTENSIONS_HELPER_H
#define TEST_AVAILABLE_VULKAN_EXTENSIONS_HELPER_H

#include <fstream>
#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "../utils/log.h"

namespace VulkanTest::Graphics {

	bool checkAvailableVulkanExtensions(std::vector<VkExtensionProperties>* extensionProperties);
    bool retrieveVulkanExtensionCount(uint32_t* extensionCount);
    bool wasVulkanExtensionCountRetrievalSuccessful(VkResult result, uint32_t extensionCount);
    bool enumerateVulkanExtensionProperties(std::vector<VkExtensionProperties>* extensionProperties, uint32_t* extensionCount);
    void logAvailableVulkanExtensions(std::vector<VkExtensionProperties>* extensionProperties);
	bool checkIfRequiredExtensionsArePresent(const std::vector<const char*>& requiredExtensions, const std::vector<VkExtensionProperties>& availableExtensions);
	bool isExtensionSupported(const std::vector<VkExtensionProperties>& availableExtensions, const std::string& extension);
	bool createVulkanInstance(VkInstance& instance, const std::vector<const char*>& requiredExtensions);
	bool readRequiredExtension(const std::string& filepath, std::vector<const char*>* requiredExtensions);
	bool enumeratePhysicalDevices(VkInstance& instance, std::vector<VkPhysicalDevice>& availableDevices);
	bool enumeratePhysicalDeviceExtensions(const VkPhysicalDevice& device, std::vector<VkExtensionProperties>& extensionProperties);
}

#endif
