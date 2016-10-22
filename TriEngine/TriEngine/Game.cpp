#include "Game.h"

namespace TriEngine {

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};


	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	static void CloseWindowCallback(GLFWwindow* glfwWindow);
	static void KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
	static void ClickCallback(GLFWwindow* glfwWindow, int button, int action, int mods);

	const char* Game::TITLE = "Stadium";


	
	/// See the header file reguarding unique_ptr
	std::unique_ptr<Game> Game::gameInstance(nullptr);

	Game::Game() {
		Debug::Log(EMessageType::INFO, "Game() Created", __FILENAME__, __LINE__);
		VDeleter<VkInstance> instance{ vkDestroyInstance };
		VDeleter<VkDebugReportCallbackEXT> callback{ instance, DestroyDebugReportCallbackEXT };
	}

	Game::~Game() {
		glfwTerminate();
		Debug::Log(EMessageType::INFO, "Game() Destroyed", __FILENAME__, __LINE__);
	}

	Game* Game::GetInstance() {
		if (gameInstance == nullptr) {
			gameInstance.reset(new Game());
		}

		return gameInstance.get();
	}

	bool Game::Initialize() {
		Debug::Log(EMessageType::INFO, "Game->Initialize()", __FILENAME__, __LINE__);
		// GLFW Init -- move this to the Window.cpp Initialize() if there will be no GLFW calls here for better abstraction
		if (!glfwInit()) {
			Debug::Log(EMessageType::FATAL_ERROR, "GLFW cannot be initialized!", __FILENAME__, __LINE__);
			return false;
		}

		windowInstance.Initialize();
		windowInstance.SetTitle(TITLE);
		windowInstance.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT); // Currently Resizing but the render area is not changed i think.

		glfwSetWindowUserPointer(windowInstance.GetWindowHandle(), this);
		glfwSetWindowCloseCallback(windowInstance.GetWindowHandle(), CloseWindowCallback);

		// Key and Character are both for Keyboard Event Polling, see documentation for the difference between the two.
		glfwSetKeyCallback(windowInstance.GetWindowHandle(), KeyCallback);
		// glfwSetCharCallback(glfwWindow, character_callback);
		glfwSetMouseButtonCallback(windowInstance.GetWindowHandle(), ClickCallback);

		// fps = 60.0;

		initVulkan();


		return true;

	}

	void Game::Run() {
		Debug::Log(EMessageType::INFO, "Game->Run()", __FILENAME__, __LINE__);
		isRunning = Initialize();
		Timer timer;
		timer.Start();

		while (isRunning) {
			timer.UpdateFrameTicks();
			Update();
			Render();
			glfwPollEvents();

			// timer.GetSleepTime(fps);
			// std::cout << "main loop running at: " << timer.GetDeltaTime() << "sec/frame" << std::endl;

		}
	}

	void Game::Update() {

		if (glfwWindowShouldClose(windowInstance.GetWindowHandle())) {
			windowInstance.Shutdown();
			isRunning = false;
		}

	}

	void Game::Render() {
		// glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(windowInstance.GetWindowHandle());
		// Each scene should have a render method, but for testing purposes you can do it here or somewhere else
	}


	// TODO: Create an abstraction between InputHandling and the Game Class
	void Game::HandleInput(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_W && action == GLFW_PRESS) {
			Debug::Print("Pressed W");
		}
	}

	void Game::HandleClick(GLFWwindow* window, int button, int action, int mods) {
		Debug::Print("Click!");
	}


	/*
	*VULKAN STUFF
	*/

	void Game::initVulkan() {
		Debug::Log(EMessageType::INFO, "		Game->InitVulkan()", __FILENAME__, __LINE__);
		createInstance();
		setupDebugCallback();
	}

	void Game::createInstance() {
		if (enableValidationLayers && !checkValidationLayerSupport()) {
			throw std::runtime_error("validation layers requested, but not available!");
		}
		
		// Application Info
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Creation Info
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = extensions.size();
		createInfo.ppEnabledExtensionNames = extensions.data();

		if (enableValidationLayers) {
			createInfo.enabledLayerCount = validationLayers.size();
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateInstance(&createInfo, nullptr, instance.replace()) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
	}

	void Game::setupDebugCallback() {
		if (!enableValidationLayers) return;

		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createInfo.pfnCallback = debugCallback;

		if (CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, callback.replace()) != VK_SUCCESS) {
			throw std::runtime_error("failed to set up debug callback!");
		}
	}

	std::vector<const char*> Game::getRequiredExtensions() {
		std::vector<const char*> extensions;

		unsigned int glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (unsigned int i = 0; i < glfwExtensionCount; i++) {
			extensions.push_back(glfwExtensions[i]);
		}

		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return extensions;
	}

	bool Game::checkValidationLayerSupport() {
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}

		return true;
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
		std::cerr << "validation layer: " << msg << std::endl;

		return VK_FALSE;
	}

	// -------------------------------------------------------------


	// ---- Callback Functions ---
	static void CloseWindowCallback(GLFWwindow* glfwWindow) {
		glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);
	}

	static void KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
		Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(glfwWindow));
		game->HandleInput(glfwWindow, key, scancode, action, mods);
	}

	static void ClickCallback(GLFWwindow* glfwWindow, int button, int action, int mods) {
		Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(glfwWindow));
		game->HandleClick(glfwWindow, button, action, mods);
	}

}