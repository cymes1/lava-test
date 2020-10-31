#include "test-helper.h"

namespace VulkanTest::Graphics {

    void logResultFailed()
    {
        Utils::Log::info("");
        Utils::Log::error("Test result: failed");
    }

    void logResultSuccess()
    {
        Utils::Log::info("");
        Utils::Log::info("Test result: success");
    }
}