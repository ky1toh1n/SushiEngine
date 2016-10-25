#ifndef KEYBOARD_H
#define KEYBOARD_H

namespace TriEngine {
	class Keyboard {
		Keyboard();
		~Keyboard();

		Keyboard(Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
		Keyboard operator = (Keyboard&) = delete;
		Keyboard operator = (Keyboard&&) = delete;

		void Initialize();
		void Delete();

	};
}

#endif