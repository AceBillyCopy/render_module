module;
#include "vulkan/vulkan.h"
#include <stdexcept>
#include <string>
#include <iostream>
export module error_handle;

export
/// @param message_Severity 消息级别
/// @param message_type 消息类别
/// @param p_callback_data 调试信息的数据
/// @param p_user_data 用户的自定义数据
VkBool32 DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT message_Severity,
                       VkDebugUtilsMessageTypeFlagsEXT message_type,
                       const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data,
                       void * p_user_data);
export
void IfFailedThrow(const VkResult& result, const std::string& error_info);

module : private;

void IfFailedThrow(const VkResult& result, const std::string& error_info) {
    if (result != VK_SUCCESS) {
        throw std::runtime_error(error_info);
    }
}
VkBool32 DebugCallback(VkDebugUtilsMessageSeverityFlagsEXT message_Severity,
                       VkDebugUtilsMessageTypeFlagsEXT message_type,
                       const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data,
                       void * p_user_data) {
    std::cerr << "validation layers info: " << p_callback_data->pMessage << '\n';
    return VK_FALSE;
}