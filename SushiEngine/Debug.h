/* DEBUG - Able to log messages to a file or a console. */
#ifndef DEBUG_H
#define DEBUG_H
/* System */
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
/* SushiEngine */
#include "Macros.h"
/* ---- */
//The following code uses the __FILE__ macro to get the file name.
//It gets rid of the file path to reduce clutter in the log file.
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
/* ---- */
namespace SushiEngine
{
	/* ---- */
	enum class EMessageType : unsigned char
	{
		S_INFO = 0,
		S_WARNING,
		S_ERROR,
		S_FATAL_ERROR
	};
	/* ---- */
	class Debug
	{
	public:
		/* Constructor */
		// Disable automatic constructor from being created
		Debug() = delete;
		NO_COPY_CONSTRUCTORS(Debug)

		/* Static methods */
		static void Init();
		static void Log(const EMessageType MsgType, const std::string& message, const std::string& filename, const int line);
		static void Print(const std::string text);
	};
}
#endif