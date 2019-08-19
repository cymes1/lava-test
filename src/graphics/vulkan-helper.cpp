#include "vulkan-helper.h"

namespace VulkanTest::Graphics {

	bool checkAvailableVulkanExtensions(std::vector<VkExtensionProperties>& extensionsProperties)
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
			Utils::Log::error("failed");
			return false;
		}
		Utils::Log::info("success");

		// stores the properties of available instance extensions
		extensionsProperties.resize(extensionsCount);

		// retrieve the properties of available instance extensions
		Utils::Log::info("Retrieving the properties of available vulkan instance externsions...");
		result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensionsProperties.data());

		if(result != VK_SUCCESS)
		{
			Utils::Log::error("failed");
			return false;
		}
		Utils::Log::info("success");

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

	bool checkIfRequiredExtensionsArePresent(const std::vector<const char*>& requiredExtensions, const std::vector<VkExtensionProperties>& availableExtensions)
	{
		// enumerate through all extensions
		for(const char* extension : requiredExtensions)
		{
			// check if it is supported
			Utils::Log::info((std::string("Checking if extension: ") + extension + " is supported...").c_str());
			if(!isExtensionSupported(availableExtensions, extension))
			{
				// report error if one of required extensions is not supported
				Utils::Log::error((std::string("Extension named ") + extension + " is not supported.").c_str());
				return false;
			}
			Utils::Log::info("supported");
		}
		return true;
	}

	bool isExtensionSupported(const std::vector<VkExtensionProperties>& availableExtensions, const std::string& extension)
	{
		for(const VkExtensionProperties& properties : availableExtensions)
		{
			if(std::string(properties.extensionName) == std::string(extension))
				return true;
		}
		return false;
	}

	bool createVulkanInstance(VkInstance& instance, const std::vector<const char*>& requiredExtensions)
	{
		VkApplicationInfo applicationInfo;
		applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		applicationInfo.pNext = nullptr;
		applicationInfo.pApplicationName = "vulkan-test";
		applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.pEngineName = "engine name";
		applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
		Utils::Log::info("Created structure VkApplicationInfo.");

		VkInstanceCreateInfo instanceCreateInfo;
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pNext = nullptr;
		instanceCreateInfo.flags = 0;
		instanceCreateInfo.pApplicationInfo = &applicationInfo;
		instanceCreateInfo.enabledLayerCount = 0;
		instanceCreateInfo.ppEnabledLayerNames = nullptr;
		instanceCreateInfo.enabledExtensionCount = requiredExtensions.size();
		instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
		Utils::Log::info("Created structure VkInstanceCreateInfo.");

		Utils::Log::info("Creating vulkan instance...");
		VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
		if((result != VK_SUCCESS) || (instance == VK_NULL_HANDLE))
		{
			Utils::Log::error("failed");
			return false;
		}

		Utils::Log::info("success");
		return true;
	}

}
