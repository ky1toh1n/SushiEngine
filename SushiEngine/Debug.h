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
//Don't include Macros.h - there's a circular dependency issue.
/* ---- */
//The following code uses the __FILE__ macro to get the file name.
//It gets rid of the file path to reduce clutter in the log file.
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
/* ---- */
namespace SushiEngine
{
	/* ---- */
	enum class EMessageType : int
	{
		S_INFO = 0b1,
		S_WARNING = 0b10,
		S_ERROR = 0b100, 
		S_FATAL_ERROR = 0b1000
	};
	/* ---- */
	class Debug
	{
	public:
		/* Constructor */
		// Disable automatic constructor from being created
		Debug() = delete;

		/* Static fields */
		static const int sConsoleFilter;
		static uint8_t sTabLevel;
		static const uint8_t sTabCap;

		/* Static methods */
		static void Init();
		static void Log(const EMessageType MsgType, const std::string& message, const std::string& filename, const int line);
		static void LogConstructor(const std::string& message, const std::string& filename, const int line);
		static void LogDeconstructor(const std::string& message, const std::string& filename, const int line);
		static void Print(const std::string text);
		static int GetObjectsConstructed();
	private:
		/* Static fields */
		static int sObjectsConstructed;
	};
}
#endif