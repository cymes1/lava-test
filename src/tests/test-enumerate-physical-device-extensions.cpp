#include "test-enumerate-physical-device-extensions.h"
#include "../utils/log.h"

namespace VulkanTest::Tests {

	TestEnumeratePhysicalDeviceExtensions::TestEnumeratePhysicalDeviceExtensions()
	{
		Utils::Log::info("Starting test: enumerate physical devices extensions.");
		Utils::Log::info("");

		// check vulkan instance extensions
		std::vector<VkExtensionProperties> availableExtensions;
		if(!Graphics::checkAvailableVulkanExtensions(&availableExtensions))
		{
			Utils::Log::error("failed");
			return;
		}

		// read required extensions from config file
		std::string filepath = "data/test-create-instance.conf";
		std::vector<const char*> requiredExtensions;
		if(!Graphics::readRequiredExtension(filepath, &requiredExtensions))
		{
			Utils::Log::error("failed");
			return;
		}

		// check if required instance extensions are present
		if(!Graphics::checkIfRequiredExtensionsArePresent(requiredExtensions, availableExtensions))
		{
			Utils::Log::error("failed");
			return;
		}

		// create vulkan instance
		VkInstance instance;
		if(!Graphics::createVulkanInstance(instance, requiredExtensions))
		{
			Utils::Log::error("failed");
			return;
		}

		// enumerate physical devices
		std::vector<VkPhysicalDevice> availableDevices;
		if(!Graphics::enumeratePhysicalDevices(instance, availableDevices))
			Utils::Log::error("failed");

		std::vector<VkExtensionProperties>* availablePhysicalDeviceExtensions;
		availablePhysicalDeviceExtensions = new std::vector<VkExtensionProperties>[availableDevices.size()];

		int index = 0;
		for(VkPhysicalDevice device : availableDevices)
		{
			Utils::Log::info(("Enumerating extensions of the " + std::to_string(index + 1) + " physical device...").c_str());
			if(!Graphics::enumeratePhysicalDeviceExtensions(device, availablePhysicalDeviceExtensions[index]))
				Utils::Log::error("failed");
			index++;
		}

		delete[] availablePhysicalDeviceExtensions;
	}
}
