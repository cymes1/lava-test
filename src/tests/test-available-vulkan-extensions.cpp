#include "test-available-vulkan-extensions.h"

namespace VulkanTest::Tests {

	TestAvailableVulkanExtensions::TestAvailableVulkanExtensions()
	{
		Utils::Log::info("Starting test: get available vulkan instance extensions.");
		Utils::Log::info("");
		if(!checkAvailableVulkanExtensions())
			Utils::Log::error("Test failed.");
	}

	bool TestAvailableVulkanExtensions::checkAvailableVulkanExtensions()
	{
		VkResult result;

		// stores the number of available instance extensions
		uint32_t extensionsCount;

		// retrieve the number of available instance extensions
		Utils::Log::info("Retrieving the number of available vulkan instance extensions...");
		result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);

		// check if success
		if(result != VK_SUCCESS || extensionsCount == 0)
		{
			Utils::Log::error("Could not get the number of instance extensions.");
			return false;
		}
		Utils::Log::info("succes");

		// stores the properties of available instance extensions
		std::vector<VkExtensionProperties> extensionsProperties(extensionsCount);

		// retrieve the properties of available instance extensions
		Utils::Log::info("Retrieving the properties of available vulkan instance externsions...");
		result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensionsProperties.data());

		if(result != VK_SUCCESS)
		{
			Utils::Log::error("Could not get the properties of instance extensions.");
			return false;
		}
		Utils::Log::info("succes");

		// log number of available instance extensions
		Utils::Log::info("");
		Utils::Log::info(("Available instance extensions: " + std::to_string(extensionsCount)).c_str());
		for(auto properties : extensionsProperties)
		{
			Utils::Log::info((std::string("\tname: ") + properties.extensionName).c_str());
			Utils::Log::info((std::string("\tversion: ") + std::to_string(properties.specVersion)).c_str());
			Utils::Log::info("");
		}

		return true;
	}

}
