#include "test-create-instance.h"
#include "../utils/log.h"

namespace VulkanTest::Tests {

	TestCreateInstance::TestCreateInstance()
	{
		Utils::Log::info("Starting test: create vulkan instance.");
		Utils::Log::info("");

		VkInstance instance;
		std::vector<VkExtensionProperties> availableExtensions;
		std::vector<const char*> requiredExtensions;
		requiredExtensions.push_back("VK_KHR_surface");

		if(!Graphics::checkAvailableVulkanExtensions(availableExtensions))
		{
			Utils::Log::error("Test failed.");
			return;
		}

		if(!Graphics::checkIfRequiredExtensionsArePresent(requiredExtensions, availableExtensions))
		{
			Utils::Log::error("Test failed.");
			return;
		}

		if(!Graphics::createVulkanInstance(instance, requiredExtensions))
			Utils::Log::error("Test failed.");
	}

}
