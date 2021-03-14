#pragma once
#include <vulkan/vulkan.h>

class DebugMessenger {
public:
	DebugMessenger();

	void Destroy();
	void SetupDebugMessenger(VkInstance instance, uint32_t enableValidationLayers);
	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

private:
	VkDebugUtilsMessengerEXT _debugMessenger;
	VkInstance _instance;
	uint32_t _enableValidationLayers;

	VkResult CreateDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo);

	void ListSupportedExtensions();
	void ListSupportedValidationLayers();
};