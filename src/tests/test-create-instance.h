#ifndef TEST_CREATE_INSTANCE_H
#define TEST_CREATE_INSTANCE_H

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "test.h"
#include "../graphics/test-available-vulkan-extensions-helper.h"
#include "../graphics/test-create-instance-helper.h"

namespace VulkanTest::Tests {

	class TestCreateInstance : public Test
	{
	public:
		TestCreateInstance();

	private:
	    void logResultFailed();
        void logResultSuccess();
	};
}

#endif
