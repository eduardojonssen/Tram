#include "DebugMessenger.h"
#include <vector>
#include <iostream>

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageSeverityFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
		std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
	}

	return VK_FALSE;
}

DebugMessenger::DebugMessenger() { }

void DebugMessenger::SetupDebugMessenger(VkInstance instance, uint32_t enableValidationLayers) {

	this->_instance = instance;
	this->_enableValidationLayers = enableValidationLayers;

	if (this->_enableValidationLayers == false) return;

	std::cout << "Running application in DEBUG mode: \n" << std::endl;
	this->ListSupportedExtensions();
	this->ListSupportedValidationLayers();

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	this->PopulateDebugMessengerCreateInfo(createInfo);

	if (this->CreateDebugUtilsMessengerEXT(&createInfo) != VK_SUCCESS) {
		throw std::runtime_error("Failed to set up debug messenger.");
	}
}

void DebugMessenger::Destroy() {

	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(this->_instance, "vkDestroyDebugUtilsMessengerEXT");

	if (func != nullptr) { func(this->_instance, this->_debugMessenger, nullptr); }
}

void DebugMessenger::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {

	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = DebugCallback;
}

VkResult DebugMessenger::CreateDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo) {

	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(this->_instance, "vkCreateDebugUtilsMessengerEXT");

	if (func != nullptr) { return func(this->_instance, pCreateInfo, nullptr, &this->_debugMessenger); }
	else { return VK_ERROR_EXTENSION_NOT_PRESENT; }
}

void DebugMessenger::ListSupportedExtensions() {

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::cout << "Available extensions:" << std::endl;

	for (const auto& extension : extensions) { std::cout << '\t' << extension.extensionName << std::endl; }

	std::cout << std::endl;
}

void DebugMessenger::ListSupportedValidationLayers() {

	uint32_t layerCount = 0;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	std::cout << "Available validation layers:" << std::endl;

	for (const auto& layer : availableLayers) { std::cout << '\t' << layer.layerName << std::endl; }

	std::cout << std::endl;
}