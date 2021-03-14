#include "VulkanRenderer.h"
#include <iostream>

class Tram {
public:
	void run() {
		initWindow();
		initRenderer();
		mainLoop();
		cleanup();
	}

private:
	GLFWwindow* window;
	VulkanRenderer* vulkanRenderer;

	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	void initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Tram", nullptr, nullptr);
		glfwSetWindowUserPointer(window, &vulkanRenderer);
		glfwSetFramebufferSizeCallback(window, vulkanRenderer->FramebufferResizeCallback);
	}

	void initRenderer() {
		vulkanRenderer = new VulkanRenderer;
		vulkanRenderer->Init(window);
	}

	void mainLoop() {
		while (glfwWindowShouldClose(window) == false) {
			glfwPollEvents();
			drawFrame();
		}
	}

	void cleanup() {

		if (vulkanRenderer != nullptr) {
			vulkanRenderer->Destroy();
			delete vulkanRenderer;
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void drawFrame() {
		vulkanRenderer->Draw();
	}
};

int main(int argc, char** argv) {

	Tram app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}