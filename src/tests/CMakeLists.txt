add_library(tests test.cpp test-available-vulkan-extensions.cpp)

target_link_libraries(tests Vulkan::Vulkan)
