#ifndef TEST_ENUMERATE_PHYSICAL_DEVICES
#define TEST_ENUMERATE_PHYSICAL_DEVICES

#include <vector>
#include <vulkan/vulkan.h>
#include "test.h"
#include "../graphics/test-available-vulkan-extensions-helper.h"

namespace VulkanTest::Tests {

	class TestEnumeratePhysicalDevices : public Test
	{
	public:
		TestEnumeratePhysicalDevices();
	};

}

#endif
