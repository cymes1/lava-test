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

	bool readRequiredExtension(const std::string& filepath, std::vector<std::string>& requiredExtensions)
	{
		std::string startPhrase = "required_instance_extensions start";
		std::string endPhrase = "required_instance_extensions end";
		std::ifstream stream(filepath);
		std::string line;
		bool controlPhraseFound = false;

		Utils::Log::info("Reading required instance extensions from config file...");

		// check if the file opened successfully
		if(!stream.is_open())
		{
			Utils::Log::error(("Can't open file " + filepath).c_str());
			Utils::Log::info("failed");
			return false;
		}

		// find start phrase in file
		while(getline(stream, line))
		{
			if(line == startPhrase)
			{
				controlPhraseFound = true;
				break;
			}
		}

		// check if start phrase was found
		if(!controlPhraseFound)
		{
			Utils::Log::error(("Can't find line \"" + startPhrase + "\" in the file: " + filepath).c_str());
			Utils::Log::info("failed");
			stream.close();
			return false;
		}
		controlPhraseFound = false;

		// read read required instance extensions from file until end phrase is found
		while(getline(stream, line))
		{
			// find end phrase in file
			if(line == endPhrase)
			{
				controlPhraseFound = true;
				break;
			}
			else // read required instance extensions into a vector
			{
				requiredExtensions.push_back(line);
			}
		}

		// check if end phrase was found
		if(!controlPhraseFound)
		{
			Utils::Log::error(("Can't find line \"" + endPhrase + "\" in the file: " + filepath).c_str());
			Utils::Log::info("failed");
			stream.close();
			return false;
		}

		// reading return success
		Utils::Log::info("success");
		stream.close();

		// list required instance extensions
		Utils::Log::info("");
		Utils::Log::info("Required instance extensions:");
		for(std::string extension : requiredExtensions)
			Utils::Log::info((std::string("\t") + extension).c_str());
		Utils::Log::info("");
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
				Utils::Log::error((std::string("Extension named ") + extension + " is not supported.\n").c_str());
				return false;
			}
			Utils::Log::info("supported");
			Utils::Log::info("");
		}
		return true;
	}

	bool isExtensionSupported(const std::vector<VkExtensionProperties>& availableExtensions, const std::string& extension)
	{
		// enumerate through all supported properties
		for(const VkExtensionProperties& properties : availableExtensions)
		{
			// check if extension is supported
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
		Utils::Log::info("");
		return true;
	}

	bool enumeratePhysicalDevices(VkInstance& instance, std::vector<VkPhysicalDevice>& availableDevices)
	{
		VkResult result;

		Utils::Log::info("Retrieving the number of available physical devices...");
		uint32_t devicesCount;
		result = vkEnumeratePhysicalDevices(instance, &devicesCount, nullptr);
		if(result != VK_SUCCESS)
		{
			Utils::Log::error("failed");
			return false;
		}
		Utils::Log::info("success");

		Utils::Log::info("Retrieving available physical devices...");
		availableDevices.resize(devicesCount);
		result = vkEnumeratePhysicalDevices(instance, &devicesCount, availableDevices.data());
		if(result != VK_SUCCESS)
		{
			Utils::Log::error("failed");
			return false;
		}
		Utils::Log::info("success");
		Utils::Log::info("");

		// log number of available instance extensions
		Utils::Log::info(("Available physical devices: " + std::to_string(devicesCount)).c_str());
		Utils::Log::info("");

		return true;
	}

	bool enumeratePhysicalDeviceExtensions(const VkPhysicalDevice& device, std::vector<VkExtensionProperties>& extensionsProperties)
	{
		VkResult result;

		// stores the number of available physical device extensions
		uint32_t extensionsCount;

		// retrieve the number of available instance extensions
		Utils::Log::info("Retrieving the number of available physical device extensions...");
		result = vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, nullptr);

		// check if success
		if(result != VK_SUCCESS || extensionsCount == 0)
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

		if(result != VK_SUCCESS)
		{
			Utils::Log::error("failed");
			return false;
		}
		Utils::Log::info("success");

		// log number of available physical device extensions
		Utils::Log::info("");
		Utils::Log::info(("Available physical device extensions: " + std::to_string(extensionsCount)).c_str());
		for(auto properties : extensionsProperties)
		{
			Utils::Log::info((std::string("\tname: ") + properties.extensionName).c_str());
			Utils::Log::info((std::string("\tversion: ") + std::to_string(properties.specVersion)).c_str());
			Utils::Log::info("");
		}

		return true;
	}
}
