#ifndef TEST_H
#define TEST_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>

namespace VulkanTest::Tests {

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test
	{
	private:
		Test*& m_currentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;

	public:
		TestMenu(Test*& currentTestPointer);

		void chooseTest();

		template<typename T>
		void registerTest(const std::string& name)
		{
			m_tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};

}

#endif
