add_library(graphics window.cpp
        test-helper.cpp
        test-available-vulkan-extensions-helper.cpp
        test-create-instance-helper.cpp
        test-enumerate-physical-devices-helper.cpp)

target_link_libraries(graphics Vulkan::Vulkan)
target_link_libraries(graphics glfw)
target_link_libraries(graphics logging)
