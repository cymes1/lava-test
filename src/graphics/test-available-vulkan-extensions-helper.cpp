#include "test-available-vulkan-extensions-helper.h"

namespace VulkanTest::Graphics {

    bool checkAvailableVulkanExtensions(std::vector<VkExtensionProperties> *extensionProperties)
    {
        uint32_t extensionCount;
        bool result = retrieveVulkanExtensionCount(&extensionCount);
        if (!result)
            return false;

        extensionProperties->resize(extensionCount);
        result = enumerateVulkanExtensionProperties(extensionProperties, &extensionCount);
        if(!result)
            return false;

        return true;
    }

    bool retrieveVulkanExtensionCount(uint32_t* extensionCount)
    {
        Utils::Log::info("Retrieving the number of available vulkan instance extensions...");
        VkResult result = vkEnumerateInstanceExtensionProperties(nullptr, extensionCount, nullptr);
        if (!wasVulkanExtensionCountRetrievalSuccessful(result, *extensionCount))
        {
            Utils::Log::error("failed");
            return false;
        }
        Utils::Log::info("success");
        return true;
    }

    bool wasVulkanExtensionCountRetrievalSuccessful(VkResult result, uint32_t extensionCount)
    {
        return result == VK_SUCCESS && extensionCount != 0;
    }

    bool enumerateVulkanExtensionProperties(std::vector<VkExtensionProperties>* extensionProperties, uint32_t* extensionCount)
    {
        Utils::Log::info("Retrieving the properties of available vulkan instance extensions...");
        VkResult result = vkEnumerateInstanceExtensionProperties(nullptr, extensionCount, extensionProperties->data());
        if (result != VK_SUCCESS) {
            Utils::Log::error("failed");
            return false;
        }
        Utils::Log::info("success");
        return true;
    }

    void logAvailableVulkanExtensions(std::vector<VkExtensionProperties>* extensionProperties)
    {
        Utils::Log::info("");
        Utils::Log::info(("Available instance extensions: " + std::to_string(extensionProperties->size())).c_str());
        for (auto properties : *extensionProperties) {
            Utils::Log::info((std::string("\tname: ") + properties.extensionName).c_str());
            Utils::Log::info((std::string("\tversion: ") + std::to_string(properties.specVersion)).c_str());
            Utils::Log::info("");
        }
    }
}
