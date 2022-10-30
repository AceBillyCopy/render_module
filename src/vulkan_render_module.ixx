module;
#include <vector>
#include <string>
#include <memory>
#include "vulkan/vulkan.h"
export module vulkan_render_module;
import error_handle;
import window;
import common.aconcepts;

using namespace std::string_literals;

export
class VulkanRender {
public:
    VulkanRender();

    VulkanRender(const VulkanRender&)=delete;
    VulkanRender(VulkanRender&& )=delete;
    VulkanRender& operator=(const VulkanRender&)=delete;
    VulkanRender& operator=(VulkanRender&&)=delete;

    ~VulkanRender();
public:
    void Init();
    void CleanUp();
private:
    void CreateInstance();
    ///  initialize vk extension
    ///  called in construct
    ///  todo: The separation is independent of the window API
    void EnableExtension();
    ///  check and enable validation layers;
    bool CheckValidationLayerSupport();
    void EnableValidationLayers(VkInstanceCreateInfo &create_info);
    std::vector<const char*> GetRequiredExtension();
    void SetDebugCallback();

    void AppendValidationLayer(CValidationLayerNameType auto name);
    void AddExtension(CExtensionNameType auto extension_name);


private:
    /// enable validation layers if "debug_flag" == true
    bool debug_flag_ = true;
    std::vector<const char*> validation_layers_;

    VkInstance instance_;
    std::vector<const char*> vk_extension_;
private:
    std::unique_ptr<Window> p_window_;
};

module : private;

void VulkanRender::EnableExtension() {
    // todo: get extension counts
    vk_extension_.push_back(p_window_->GetVkExtension());
}

VulkanRender::VulkanRender() {
    EnableExtension();
}
VulkanRender::~VulkanRender() {
    CleanUp();
}

void VulkanRender::Init() {
    CreateInstance();
}

void VulkanRender::CleanUp() {
    vkDestroyInstance(instance_, nullptr);
    if(!p_window_) p_window_->CleanUp();
}

void VulkanRender::CreateInstance() {
    VkApplicationInfo app_info{};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "vulkan render demo";
    VkInstanceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    create_info.enabledExtensionCount = vk_extension_.size();
    create_info.ppEnabledExtensionNames = vk_extension_.data();
    /// validation layers;
    // enable validation layers
    EnableValidationLayers(create_info);
    IfFailedThrow(vkCreateInstance(&create_info, nullptr, &instance_),
                  "failed to create vkInstance"s);
}

void VulkanRender::EnableValidationLayers(VkInstanceCreateInfo &create_info) {
    // todo: improve error handle
    if (debug_flag_ && !validation_layers_.empty() && !CheckValidationLayerSupport()) {
        IfFailedThrow(VK_ERROR_UNKNOWN, "failed to enable validation"s);
    } else {
        create_info.ppEnabledLayerNames = validation_layers_.data();
        create_info.enabledLayerCount = validation_layers_.size();
        AddExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        // update create info about extension
        create_info.enabledExtensionCount = vk_extension_.size();
        create_info.ppEnabledExtensionNames = vk_extension_.data();
    }


}

bool VulkanRender::CheckValidationLayerSupport() {
    ::uint32_t layer_count = 0;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
    std::vector<VkLayerProperties> available_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());
    for (auto layers_name : validation_layers_) {
        bool layer_found = false;
        for (const auto& layer_properties : available_layers) {
            if (std::strcmp(layers_name, layer_properties.layerName) == 0) {
                layer_found = true;
                break;
            }
        }
        if (!layer_found) {
            return false;
        }
    }
    return true;
}

void VulkanRender::AppendValidationLayer(CValidationLayerNameType auto name) {
    validation_layers_.push_back(name);
}

std::vector<const char *> VulkanRender::GetRequiredExtension() {
    return std::vector<const char *>();
}

void VulkanRender::AddExtension(CExtensionNameType auto extension_name) {
    vk_extension_.push_back(extension_name);
}

void VulkanRender::SetDebugCallback() {
    if (!debug_flag_) return;
    VkDebugUtilsMessengerCreateInfoEXT debug_callback_create_info {};
    debug_callback_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debug_callback_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debug_callback_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debug_callback_create_info.pfnUserCallback = DebugCallback;
    debug_callback_create_info.pUserData = nullptr;
}
