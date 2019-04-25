add_executable(test main.cpp game.cpp)

add_subdirectory(utils)
add_subdirectory(graphics)

target_link_libraries(test Vulkan::Vulkan)
target_link_libraries(test glfw)
target_link_libraries(test logging)
target_link_libraries(test graphics)
