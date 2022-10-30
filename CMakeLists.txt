cmake_minimum_required(VERSION 3.24)
project(render_module)

include_directories("C:\\VulkanSDK\\1.3.224.1\\Include" "./third_party/glfw-3.3.8.bin.WIN64/include/")
link_directories("C:\\VulkanSDK\\1.3.224.1\\Lib" "./third_party/glfw-3.3.8.bin.WIN64/lib-vc2022")

set(CMAKE_CXX_STANDARD 23)

add_executable(render_module main.cpp src/vulkan_render_module.ixx src/error_handle.ixx src/window.ixx src/common.concepts.ixx src/common.ixx src/tools.ixx)
target_link_libraries(render_module vulkan-1.lib VkLayer_utils.lib)
