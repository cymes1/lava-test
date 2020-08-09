#include <stdexcept>

#include "game.h"
#include "utils/log.h"

int main()
{
	VulkanTest::Game game;

	try
	{
		game.run();
	}
	catch(const std::runtime_error& e)
	{
		VulkanTest::Utils::Log::error(e.what());
		return -1;
	}

	game.clean();
	return 0;
}
