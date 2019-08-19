#include "test-create-instance.h"
#include "../utils/log.h"

namespace VulkanTest::Tests {

	TestCreateInstance::TestCreateInstance()
	{
		Utils::Log::info("Starting test: create vulkan instance.");
		Utils::Log::info("");

		VkInstance instance;
		std::vector<VkExtensionProperties> availableExtensions;

		if(!Graphics::checkAvailableVulkanExtensions(availableExtensions))
		{
			Utils::Log::error("failed");
			return;
		}

		Utils::Log::info("Reading required instance extensions from config file...");
		std::string filepath = "data/test-create-instance.conf";
		std::vector<std::string> stringRequiredExtensions;
		if(!readRequiredExtension(filepath, stringRequiredExtensions))
		{
			Utils::Log::error("failed");
			return;
		}
		Utils::Log::info("success");
		Utils::Log::info("");

		// convert from vector<std::string> to vector<const char*>
		std::vector<const char*> requiredExtensions;
		requiredExtensions.resize(stringRequiredExtensions.size());
		for(int i = 0; i < stringRequiredExtensions.size(); i++)
			requiredExtensions[i] = stringRequiredExtensions[i].c_str();

		Utils::Log::info("Required instance extensions:");
		for(const char* extension : requiredExtensions)
			Utils::Log::info((std::string("\t") + extension).c_str());
		Utils::Log::info("");


		Utils::Log::info("Checking if required instance extensions are present...");
		if(!Graphics::checkIfRequiredExtensionsArePresent(requiredExtensions, availableExtensions))
		{
			Utils::Log::error("failed");
			return;
		}
		Utils::Log::info("success");
		Utils::Log::info("");

		if(!Graphics::createVulkanInstance(instance, requiredExtensions))
			Utils::Log::error("failed");
	}

	bool TestCreateInstance::readRequiredExtension(const std::string& filepath, std::vector<std::string>& requiredExtensions)
	{
		std::string startPhrase = "required_instance_extensions start";
		std::string endPhrase = "required_instance_extensions end";
		std::ifstream stream(filepath);
		std::string line;
		bool controlPhraseFound = false;

		// check if the file opened successfully
		if(!stream.is_open())
		{
			Utils::Log::error(("Can't open file " + filepath).c_str());
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
			stream.close();
			return false;
		}

		stream.close();
		return true;
	}
}
