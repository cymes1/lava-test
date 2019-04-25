#ifndef GAME_H
#define GAME_H

#include "graphics/window.h"

namespace VulkanTest {

	class Game
	{
	private:
		Graphics::Window m_window;

	public:
		Game();
		void run();
		void clean();
	};
}

#endif
