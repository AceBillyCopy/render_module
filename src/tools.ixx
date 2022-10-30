// todo: improve source code structure
module;
#include <string>
#include "vulkan/vulkan.h"

export module tools;
import common.aconcepts;
using namespace std::string_literals;

export
template<CallableType Func>
Func GetExtFunctionPointer(VkInstance instance, const std::string& function_name) {
    return reinterpret_cast<Func>(vkGetInstanceProcAddr(instance, function_name.c_str()));
}

export
VkResult CreateDebugUtilsMessengerProxyFunc(VkInstance instance,
                                            const VkDebugUtilsMessengerCreateInfoEXT* p_create_info,
                                            const VkDebugUtilsMessengerEXT* p_callback);

module : private;

VkResult CreateDebugUtilsMessengerProxyFunc(VkInstance instance,
                                            const VkDebugUtilsMessengerCreateInfoEXT* p_create_info,
                                            const VkDebugUtilsMessengerEXT* p_callback) {
    auto func =
            GetExtFunctionPointer<PFN_vkCreateDebugUtilsMessengerEXT>(instance, "vkCreateDebugUtilsMessengerEXT"s);
    if (!func) return VK_ERROR_EXTENSION_NOT_PRESENT;
    return VK_SUCCESS;
}