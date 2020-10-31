#include "test-enumerate-physical-devices.h"

namespace VulkanTest::Tests {

	TestEnumeratePhysicalDevices::TestEnumeratePhysicalDevices()
	{
		Utils::Log::info("Starting test: enumerate physical devices.");
		Utils::Log::info("");

		std::vector<VkExtensionProperties> availableExtensions;
		bool result = Graphics::checkAvailableVulkanExtensions(&availableExtensions);
		if(!result)
		{
		    Graphics::logResultFailed();
			return;
		}

		std::string filepath = "data/test-create-instance.conf";
		std::vector<const char*> requiredExtensions;
        result = Graphics::readRequiredExtension(filepath, &requiredExtensions);
        if (!result)
        {
            Graphics::logResultFailed();
            Graphics::deleteRequiredExtensions(requiredExtensions);
            return;
        }

        result = Graphics::checkIfRequiredExtensionsArePresent(requiredExtensions, availableExtensions);
        if (!result)
        {
            Graphics::logResultFailed();
            Graphics::deleteRequiredExtensions(requiredExtensions);
            return;
        }

        VkInstance instance;
        if (!Graphics::createVulkanInstance(instance, requiredExtensions))
        {
            Graphics::logResultFailed();
            Graphics::deleteRequiredExtensions(requiredExtensions);
            return;
        }

		std::vector<VkPhysicalDevice> availableDevices;
        result = Graphics::enumeratePhysicalDevices(instance, availableDevices);
        if(!result)
        {
            Graphics::logResultFailed();
            Graphics::deleteRequiredExtensions(requiredExtensions);
            return;
        }

        Graphics::logPhysicalDeviceCount(availableDevices.size());
        Graphics::deleteRequiredExtensions(requiredExtensions);
        Graphics::logResultSuccess();
	}
}