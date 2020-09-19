#ifndef TEST_AVAILABLE_VULKAN_EXTENSIONS_HELPER_H
#define TEST_AVAILABLE_VULKAN_EXTENSIONS_HELPER_H

#include <vector>
#include <vulkan/vulkan.h>
#include "../utils/log.h"

namespace VulkanTest::Graphics {

	bool checkAvailableVulkanExtensions(std::vector<VkExtensionProperties>* extensionProperties);
    bool retrieveVulkanExtensionCount(uint32_t* extensionCount);
    bool wasVulkanExtensionCountRetrievalSuccessful(VkResult result, uint32_t extensionCount);
    bool enumerateVulkanExtensionProperties(std::vector<VkExtensionProperties>* extensionProperties, uint32_t* extensionCount);
    void logAvailableVulkanExtensions(std::vector<VkExtensionProperties>* extensionProperties);
}

#endif
