module;

#include <string>
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <vector>

export module window;
import common.aconcepts;

export
class Window {
public:
    CExtensionNameContainerType auto GetVkExtension();
    // todo: configure window base info from outside
    // common interface;
    void Init();
    void CreateWindow();
    void CleanUp();
    void EventLoop();
private:
    // common data
    int window_width_, window_height;
    std::string window_name_;
    // improve
    // specify type by different platform
    GLFWwindow* p_window_handle_ = nullptr;
};

module : private;
void Window::CleanUp() {
    glfwDestroyWindow(p_window_handle_);
    glfwTerminate();
}

void Window::Init() {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void Window::CreateWindow() {
    // todo: add chose monitor;
    // improve source code structure
    p_window_handle_ =
            glfwCreateWindow(window_width_, window_height, window_name_.c_str(),
                             nullptr, nullptr);
    // todo: error handle
    if (p_window_handle_ != nullptr) {;}
}

void Window::EventLoop() {
    while(!glfwWindowShouldClose(p_window_handle_)) {
        glfwPollEvents();
    }
}
CExtensionNameContainerType auto Window::GetVkExtension(){
    ::uint32_t  glfw_extension_count = 0;
    const char** extension_name;
    extension_name = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    return std::vector<const char*>(extension_name, extension_name + glfw_extension_count);
}