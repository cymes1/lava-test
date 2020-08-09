#include "game.h"
#include "utils/log.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool isEscapePressed = false;

namespace VulkanTest {

	Game::Game()
		: m_window(800, 600, "lava"), currentTest(nullptr)
	{
        menu = new Tests::TestMenu(currentTest);

		// set input callback
		glfwSetKeyCallback(m_window.handle(), keyCallback);
		
		menu->registerTest<Tests::TestAvailableVulkanExtensions>("Check available vulkan extensions.");
		menu->registerTest<Tests::TestCreateInstance>("Create vulkan instance.");
		menu->registerTest<Tests::TestEnumeratePhysicalDevices>("Enumerate available physical devices.");
		menu->registerTest<Tests::TestEnumeratePhysicalDeviceExtensions>("Enumerate available physical devices extensions.");
		menu->chooseTest();
	}

	void Game::run()
	{
		while(!glfwWindowShouldClose(m_window.handle()))
		{
			if(currentTest)
			{
				if(currentTest != menu && isEscapePressed)
				{
					delete currentTest;
                    currentTest = menu;
					menu->chooseTest();
				}
				currentTest->OnUpdate(0);
				currentTest->OnRender();
				currentTest->OnImGuiRender();
			}

			glfwPollEvents();
		}
	}

	void Game::clean()
	{
		delete currentTest;
		if(currentTest != menu)
			delete menu;
	}
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		if(action == GLFW_PRESS)
			isEscapePressed = true;
		else
			isEscapePressed = false;
	}
}
