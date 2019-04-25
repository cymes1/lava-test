#include "game.h"
#include "utils/log.h"

namespace VulkanTest {

	Game::Game()
		: m_window(800, 600, "lava")
	{
	}

	void Game::run()
	{
		while(!glfwWindowShouldClose(m_window.handle()))
		{
			glfwPollEvents();
		}
	}

	void Game::clean()
	{}
}
