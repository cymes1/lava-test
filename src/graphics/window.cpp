#include "window.h"

namespace VulkanTest::Graphics {

	Window::Window(int width, int height, const char* title)
		: width(width), height(height)
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        windowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
	}

	Window::~Window()
	{
		glfwDestroyWindow(windowHandle);
		glfwTerminate();
	}

	GLFWwindow* Window::handle()
	{
		return windowHandle;
	}
}
