#include "test-create-instance.h"

namespace VulkanTest::Tests {

	TestCreateInstance::TestCreateInstance()
	{
        Utils::Log::info("Starting test: create vulkan instance.");
        Utils::Log::info("");

        std::vector<VkExtensionProperties> availableExtensions;
        bool result = Graphics::checkAvailableVulkanExtensions(&availableExtensions);
        if (!result)
        {
            logResultFailed();
            return;
        }

        std::string filepath = "data/test-create-instance.conf";
        std::vector<const char*> requiredExtensions;
        result = Graphics::readRequiredExtension(filepath, &requiredExtensions);
        if (!result)
        {
            logResultFailed();
            return;
        }
        Graphics::logRequiredExtension(requiredExtensions);

        result = Graphics::checkIfRequiredExtensionsArePresent(requiredExtensions, availableExtensions);
        if (!result)
        {
            logResultFailed();
            return;
        }

        VkInstance instance;
        if (!Graphics::createVulkanInstance(instance, requiredExtensions))
            logResultFailed();
        else
            logResultSuccess();

		for(const char* extension : requiredExtensions)
		    delete[] extension;
	}

	void TestCreateInstance::logResultFailed()
    {
        Utils::Log::info("");
        Utils::Log::error("Test result: failed");
    }

    void TestCreateInstance::logResultSuccess()
    {
        Utils::Log::info("");
        Utils::Log::error("Test result: success");
    }
}
