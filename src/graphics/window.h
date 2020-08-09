#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include "../utils/log.h"

namespace VulkanTest::Graphics {

	class Window
	{
	private:
		int width;
		int height;
		GLFWwindow* windowHandle;

	public:
		Window(int width, int height, const char* title);
		~Window();

		GLFWwindow* handle();
	};
}

#endif
