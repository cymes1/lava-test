#include "game.h"
#include "utils/log.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool isEscapePressed = false;

namespace VulkanTest {

	Game::Game()
		: m_window(800, 600, "lava")
	{
		m_menu = new Tests::TestMenu(m_currentTest);

		// set input callback
		glfwSetKeyCallback(m_window.handle(), keyCallback);
		
		m_menu->registerTest<Tests::TestAvailableVulkanExtensions>("Check available vulkan extensions.");
		m_menu->registerTest<Tests::TestCreateInstance>("Create vulkan instance.");
		m_menu->chooseTest();
	}

	void Game::run()
	{
		while(!glfwWindowShouldClose(m_window.handle()))
		{
			if(m_currentTest)
			{
				if(m_currentTest != m_menu && isEscapePressed)
				{
					delete m_currentTest;
					m_currentTest = m_menu;
					m_menu->chooseTest();
				}
				m_currentTest->OnUpdate(0);
				m_currentTest->OnRender();
				m_currentTest->OnImGuiRender();
			}

			glfwPollEvents();
		}
	}

	void Game::clean()
	{
		delete m_currentTest;
		if(m_currentTest != m_menu)
			delete m_menu;
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
