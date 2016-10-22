#ifndef GAME_H
#define GAME_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <memory>
#include <vector>
#include <cstring>


#include "Window.h"
#include "InputManager.h"
#include "Timer.h"
#include "VDeleter.h"


namespace TriEngine {

	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);

	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif

	class Game {
	public:
		const static char* TITLE;
		const static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;

		Game(const Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(const Game&) = delete;
		Game& operator=(Game&&) = delete;

	private:
		Game();
		~Game();

		Window windowInstance;
		InputManager inputManger;

		bool isRunning;
		unsigned int fps;

		///std::unique_ptr is a smart pointer that destroys the object it point to when the unique_ptr goes out of scope.
		static std::unique_ptr<Game> gameInstance;

		/// Since my destructor is private the template std::unique_ptr needs access so I made it a friend.
		/// However, std::default_delete is the default destruction policy used by std::unique_ptr 
		/// when no deleter is specified, therefore I'll make std::default_delete my friend as well. 
		friend std::default_delete<Game>;

		bool Initialize();
		void initVulkan();
		void Update();
		void Render();

		// Vulkan

		VDeleter<VkInstance> instance;
		VDeleter<VkDebugReportCallbackEXT> callback;
		bool checkValidationLayerSupport();


	public:
		static Game* GetInstance();
		void Run();
		// Temporary Params, checking if it works
		void HandleInput(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
		void HandleClick(GLFWwindow* glfwWindow, int button, int action, int mods);

		// Vulkan

		void createInstance();
		void setupDebugCallback();
		std::vector<const char*> getRequiredExtensions();
		
	};
}

#endif