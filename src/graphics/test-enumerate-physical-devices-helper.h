#ifndef VULKAN_TEST_TEST_ENUMERATE_PHYSICAL_DEVICES_HELPER_H
#define VULKAN_TEST_TEST_ENUMERATE_PHYSICAL_DEVICES_HELPER_H

#include <vector>
#include <vulkan/vulkan.h>
#include "../utils/log.h"

namespace VulkanTest::Graphics {

    bool enumeratePhysicalDevices(const VkInstance& instance, std::vector<VkPhysicalDevice>& availableDevices);
    bool retrievePhysicalDeviceCount(uint32_t* deviceCount, const VkInstance& instance);
    bool retrievePhysicalDevices(uint32_t deviceCount,
                                 std::vector<VkPhysicalDevice>& availableDevices,
                                 const VkInstance& instance);
    bool logPhysicalDeviceCount(uint32_t deviceCount);
    bool enumeratePhysicalDeviceExtensions(const VkPhysicalDevice& device, std::vector<VkExtensionProperties>& extensionProperties);
}

#endif
