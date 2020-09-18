#ifndef TEST_ENUMERATE_PHYSICAL_DEVICE_EXTENSIONS
#define TEST_ENUMERATE_PHYSICAL_DEVICE_EXTENSIONS

#include <vector>
#include <vulkan/vulkan.h>
#include "test.h"
#include "../graphics/test-available-vulkan-extensions-helper.h"

namespace VulkanTest::Tests {

	class TestEnumeratePhysicalDeviceExtensions : public Test
	{
	public:
		TestEnumeratePhysicalDeviceExtensions();
	};

}

#endif
