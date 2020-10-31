#include "test-create-instance-helper.h"

namespace VulkanTest::Graphics {

    bool readRequiredExtension(const std::string& filepath, std::vector<const char*>* requiredExtensions)
    {
        std::string startPhrase = "required_instance_extensions start";
        std::string endPhrase = "required_instance_extensions end";
        std::ifstream stream(filepath);
        std::string line;

        Utils::Log::info("Reading required instance extensions from config file...");

        if(!stream.is_open())
        {
            Utils::Log::error(("Can't open file " + filepath).c_str());
            Utils::Log::info("failed");
            return false;
        }

        bool controlPhraseFound = findStartPhraseInFile(stream, startPhrase);
        if(!controlPhraseFound)
        {
            Utils::Log::error(("Can't find line \"" + startPhrase + "\" in the file: " + filepath).c_str());
            Utils::Log::info("failed");
            stream.close();
            return false;
        }

        controlPhraseFound = readFileUntilEndPhraseIsFound(stream, requiredExtensions, endPhrase);
        if(!controlPhraseFound)
        {
            Utils::Log::error(("Can't find line \"" + endPhrase + "\" in the file: " + filepath).c_str());
            Utils::Log::info("failed");
            stream.close();
            return false;
        }

        Utils::Log::info("success");
        stream.close();
        return true;
    }

    bool findStartPhraseInFile(std::ifstream& stream, const std::string& startPhrase)
    {
        std::string line;
        while(getline(stream, line))
        {
            if(line == startPhrase)
                return true;
        }
        return false;
    }

    bool readFileUntilEndPhraseIsFound(std::ifstream& stream, std::vector<const char*>* requiredExtensions, const std::string& endPhrase)
    {
        std::string line;
        while(getline(stream, line))
        {
            if(line != endPhrase)
            {
                char* temp = createCharPointerFrom(line);
                requiredExtensions->push_back(temp);
            }
            else
                return true;
        }
        return false;
    }

    char* createCharPointerFrom(const std::string& line)
    {
        char* charPointer = new char[line.size() + 1];
        line.copy(charPointer, line.size(), 0);
        charPointer[line.size()] = '\0';
        return charPointer;
    }

    void logRequiredExtension(const std::vector<const char*>& requiredExtensions)
    {
        Utils::Log::info("");
        Utils::Log::info("Required instance extensions:");
        for(const char* extension : requiredExtensions)
            Utils::Log::info((std::string("\t") + extension).c_str());
        Utils::Log::info("");
    }

    bool checkIfRequiredExtensionsArePresent(const std::vector<const char*>& requiredExtensions, const std::vector<VkExtensionProperties>& availableExtensions)
    {
        for(const char* extension : requiredExtensions)
        {
            Utils::Log::info((std::string("Checking if extension: ") + extension + " is supported...").c_str());
            if(!isExtensionSupported(extension, availableExtensions))
            {
                Utils::Log::error((std::string("Extension named ") + extension + " is not supported.\n").c_str());
                return false;
            }
            Utils::Log::info("supported");
        }
        return true;
    }

    bool isExtensionSupported(const char* extension, const std::vector<VkExtensionProperties>& availableExtensions)
    {
        for(const VkExtensionProperties& properties : availableExtensions)
        {
            if(strcmp(properties.extensionName, extension) == 0)
                return true;
        }
        return false;
    }

    bool createVulkanInstance(VkInstance& instance, const std::vector<const char*>& requiredExtensions)
    {
        VkApplicationInfo applicationInfo;
        fillInApplicationInfo(applicationInfo);

        VkInstanceCreateInfo instanceCreateInfo;
        fillInInstanceCreateInfo(instanceCreateInfo, applicationInfo, requiredExtensions);

        Utils::Log::info("Creating vulkan instance...");
        VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
        if(wasInstanceCreationSuccessful(result, instance))
        {
            Utils::Log::error("failed");
            return false;
        }

        Utils::Log::info("success");
        return true;
    }

    void fillInApplicationInfo(VkApplicationInfo& applicationInfo)
    {
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pNext = nullptr;
        applicationInfo.pApplicationName = "vulkan-test";
        applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.pEngineName = "engine name";
        applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
        Utils::Log::info("Created structure VkApplicationInfo.");
    }

    void fillInInstanceCreateInfo(VkInstanceCreateInfo& instanceCreateInfo,
                                  const VkApplicationInfo& applicationInfo,
                                  const std::vector<const char*>& requiredExtensions)
    {
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = nullptr;
        instanceCreateInfo.flags = 0;
        instanceCreateInfo.pApplicationInfo = &applicationInfo;
        instanceCreateInfo.enabledLayerCount = 0;
        instanceCreateInfo.ppEnabledLayerNames = nullptr;
        instanceCreateInfo.enabledExtensionCount = requiredExtensions.size();
        instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
        Utils::Log::info("Created structure VkInstanceCreateInfo.");
    }

    bool wasInstanceCreationSuccessful(VkResult result, const VkInstance& instance)
    {
        return (result != VK_SUCCESS) || (instance == VK_NULL_HANDLE);
    }

    void deleteRequiredExtensions(const std::vector<const char*>& requiredExtensions)
    {
        for(const char* extension : requiredExtensions)
            delete[] extension;
    }
}