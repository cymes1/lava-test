#include "test-available-vulkan-extensions.h"

namespace VulkanTest::Tests {

	TestAvailableVulkanExtensions::TestAvailableVulkanExtensions()
	{
		Utils::Log::info("Starting test: get available vulkan instance extensions.");
		Utils::Log::info("");

		std::vector<VkExtensionProperties> availableExtensions;
		if(!Graphics::checkAvailableVulkanExtensions(availableExtensions))
			Utils::Log::error("failed.");
	}
}
