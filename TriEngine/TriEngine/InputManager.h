#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

namespace TriEngine {
	class InputManager {
	public:
		InputManager();
		~InputManager();

		InputManager(InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		InputManager operator = (InputManager&) = delete;
		InputManager operator = (InputManager&&) = delete;
	};
}

#endif