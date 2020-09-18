add_library(graphics window.cpp test-available-vulkan-extensions-helper.cpp)

target_link_libraries(graphics Vulkan::Vulkan)
target_link_libraries(graphics glfw)
target_link_libraries(graphics logging)
