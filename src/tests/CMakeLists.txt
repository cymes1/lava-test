add_library(tests test.cpp
	test-available-vulkan-extensions.cpp
	test-create-instance.cpp
	test-enumerate-physical-devices.cpp
	test-enumerate-physical-device-extensions.cpp)

target_link_libraries(tests Vulkan::Vulkan)
target_link_libraries(tests graphics)
