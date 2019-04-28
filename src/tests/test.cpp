#include "test.h"

namespace VulkanTest::Tests {

	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_currentTest(currentTestPointer)
	{ }

	void TestMenu::chooseTest()
	{
		int chosenTest;

		std::cout << "Available tests:" << std::endl;
		for(int i = 0; i < m_tests.size(); i++)
			std::cout << "\t" << i + 1 << ") " << m_tests[i].first << std::endl;
		std::cout << "Choose test: ";
		std::cin >> chosenTest;

		m_currentTest = m_tests[chosenTest - 1].second();
	}
}
