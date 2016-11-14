// DEBUG - Able to log messaes to a file or a console.
#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>

//The following code uses the __FILE__ macro to get the file name.
//It gets rid of the file path to reduce clutter in the log file.
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

namespace SushiEngine
{
	enum class EMessageType : unsigned char 
	{
		S_INFO = 0,
		S_WARNING,
		S_ERROR,
		S_FATAL_ERROR
	};

	class Debug
	{
	public:
		// Disable automatic constructor from being created
		Debug() = delete;

		// Kill any default constructor the compiler might create.
		Debug(const Debug&) = delete;
		Debug(Debug&&) = delete;
		Debug& operator=(const Debug&) = delete;
		Debug& operator=(Debug&&) = delete;

		static void Init();
		static void Log(const EMessageType MsgType, const std::string& message, const std::string& filename, const int line);
		static void Print(const std::string text);
	};
}
#endif