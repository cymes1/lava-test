#include "test-enumerate-physical-devices-helper.h"

namespace VulkanTest::Graphics {

    bool enumeratePhysicalDevices(const VkInstance &instance, std::vector<VkPhysicalDevice> &availableDevices)
    {
        uint32_t deviceCount;
        bool result = retrievePhysicalDeviceCount(&deviceCount, instance);
        if (!result)
            return false;

        result = retrievePhysicalDevices(deviceCount, availableDevices, instance);
        if (!result)
            return false;

        return true;
    }

    bool retrievePhysicalDeviceCount(uint32_t *deviceCount, const VkInstance &instance)
    {
        Utils::Log::info("Retrieving the number of available physical devices...");
        VkResult result = vkEnumeratePhysicalDevices(instance, deviceCount, nullptr);
        if (result != VK_SUCCESS)
        {
            Utils::Log::error("failed");
            return false;
        }
        Utils::Log::info("success");
        return true;
    }

    bool retrievePhysicalDevices(uint32_t deviceCount,
                                 std::vector<VkPhysicalDevice> &availableDevices,
                                 const VkInstance &instance)
    {
        Utils::Log::info("Retrieving available physical devices...");
        availableDevices.resize(deviceCount);
        VkResult result = vkEnumeratePhysicalDevices(instance, &deviceCount, availableDevices.data());
        if (result != VK_SUCCESS)
        {
            Utils::Log::error("failed");
            return false;
        }
        Utils::Log::info("success");
        return true;
    }

    bool logPhysicalDeviceCount(uint32_t deviceCount)
    {
        Utils::Log::info("");
        Utils::Log::info(("Available physical devices: " + std::to_string(deviceCount)).c_str());
        Utils::Log::info("");
    }

    bool enumeratePhysicalDeviceExtensions(const VkPhysicalDevice &device,
                                           std::vector<VkExtensionProperties> &extensionsProperties)
    {
        VkResult result;

        // stores the number of available physical device extensions
        uint32_t extensionsCount;

        // retrieve the number of available instance extensions
        Utils::Log::info("Retrieving the number of available physical device extensions...");
        result = vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, nullptr);

        // check if success
        if (result != VK_SUCCESS || extensionsCount == 0)
        {
            Utils::Log::error("failed");
            return false;
        }
        Utils::Log::info("success");

        // stores the properties of available physical device extensions
        extensionsProperties.resize(extensionsCount);

        // retrieve the properties of available physical device extensions
        Utils::Log::info("Retrieving the properties of available physical device externsions...");
        result = vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, extensionsProperties.data());

        if (result != VK_SUCCESS)
        {
            Utils::Log::error("failed");
            return false;
        }
        Utils::Log::info("success");

        // log number of available physical device extensions
        Utils::Log::info("");
        Utils::Log::info(("Available physical device extensions: " + std::to_string(extensionsCount)).c_str());
        for (auto properties : extensionsProperties)
        {
            Utils::Log::info((std::string("\tname: ") + properties.extensionName).c_str());
            Utils::Log::info((std::string("\tversion: ") + std::to_string(properties.specVersion)).c_str());
            Utils::Log::info("");
        }

        return true;
    }
}