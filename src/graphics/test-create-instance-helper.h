#ifndef VULKAN_TEST_TEST_CREATE_INSTANCE_HELPER_H
#define VULKAN_TEST_TEST_CREATE_INSTANCE_HELPER_H

#include <fstream>
#include <cstring>
#include <vector>
#include <vulkan/vulkan.h>
#include "../utils/log.h"

namespace VulkanTest::Graphics {

    bool readRequiredExtension(const std::string& filepath, std::vector<const char*>* requiredExtensions);
    bool findStartPhraseInFile(std::ifstream& stream, const std::string& startPhrase);
    bool readFileUntilEndPhraseIsFound(std::ifstream& stream, std::vector<const char*>* requiredExtensions, const std::string& endPhrase);
    char* createCharPointerFrom(const std::string& line);
    void logRequiredExtension(const std::vector<const char*>& requiredExtensions);
    bool checkIfRequiredExtensionsArePresent(const std::vector<const char*>& requiredExtensions, const std::vector<VkExtensionProperties>& availableExtensions);
    bool isExtensionSupported(const char* extension, const std::vector<VkExtensionProperties>& availableExtensions);
    bool createVulkanInstance(VkInstance& instance, const std::vector<const char*>& requiredExtensions);
    void fillInApplicationInfo(VkApplicationInfo& applicationInfo);
    void fillInInstanceCreateInfo(VkInstanceCreateInfo& instanceCreateInfo, const VkApplicationInfo& applicationInfo, const std::vector<const char*>& requiredExtensions);
    bool wasInstanceCreationSuccessful(VkResult result, const VkInstance& instance);
    void deleteRequiredExtensions(const std::vector<const char*>& requiredExtensions);
}

#endif
