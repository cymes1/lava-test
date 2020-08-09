#include "test-enumerate-physical-devices.h"
#include "../utils/log.h"

namespace VulkanTest::Tests {

	TestEnumeratePhysicalDevices::TestEnumeratePhysicalDevices()
	{
		Utils::Log::info("Starting test: enumerate physical devices.");
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
	}
}
