#include "test-create-instance.h"
#include "../utils/log.h"

namespace VulkanTest::Tests {

	TestCreateInstance::TestCreateInstance()
	{
		Utils::Log::info("Starting test: create vulkan instance.");
		Utils::Log::info("");

		std::vector<VkExtensionProperties> availableExtensions;
		if(!Graphics::checkAvailableVulkanExtensions(&availableExtensions))
		{
			Utils::Log::error("Test result: failed");
			return;
		}

		std::string filepath = "data/test-create-instance.conf";
		std::vector<const char*> requiredExtensions;
		if(!Graphics::readRequiredExtension(filepath, &requiredExtensions))
		{
			Utils::Log::error("Test result: failed");
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
			Utils::Log::error("failed");
	}
}
