add_executable(vulkan-test main.cpp game.cpp)

add_subdirectory(utils)
add_subdirectory(graphics)
add_subdirectory(tests)

target_link_libraries(vulkan-test Vulkan::Vulkan)
target_link_libraries(vulkan-test glfw)
target_link_libraries(vulkan-test logging)
target_link_libraries(vulkan-test graphics)
target_link_libraries(vulkan-test tests)
