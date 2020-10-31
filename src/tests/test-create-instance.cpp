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
            Graphics::logResultFailed();
            return;
        }

        std::string filepath = "data/test-create-instance.conf";
        std::vector<const char*> requiredExtensions;
        result = Graphics::readRequiredExtension(filepath, &requiredExtensions);
        if (!result)
        {
            Graphics::logResultFailed();
            Graphics::deleteRequiredExtensions(requiredExtensions);
            return;
        }
        Graphics::logRequiredExtension(requiredExtensions);

        result = Graphics::checkIfRequiredExtensionsArePresent(requiredExtensions, availableExtensions);
        if (!result)
        {
            Graphics::logResultFailed();
            Graphics::deleteRequiredExtensions(requiredExtensions);
            return;
        }

        VkInstance instance;
        if (!Graphics::createVulkanInstance(instance, requiredExtensions))
            Graphics::logResultFailed();
        else
            Graphics::logResultSuccess();

        Graphics::deleteRequiredExtensions(requiredExtensions);
	}
}
