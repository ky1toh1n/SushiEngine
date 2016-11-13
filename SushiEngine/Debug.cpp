#include "Debug.h"

namespace SushiEngine
{

	void Debug::Init() 
	{
		std::ofstream out;
		out.open("GameLog.txt", std::ios::out); // Replace the existing text file
		out << std::endl;
		out.close();
	}

	void Debug::Log(const EMessageType MsgType, const std::string& message, const std::string& filename, const int line)
	{
		std::ofstream out;
		out.open("GameLog.txt", std::ios::app | std::ios::out); // Append to the current text file

		switch (MsgType)
		{
		case EMessageType::S_INFO:
			out << "INFO: " << message << " (" << filename << ":" << line << ")" << std::endl;
			break;
		case EMessageType::S_WARNING:
			out << "WARNING: " << message << " (" << filename << ":" << line << ")" << std::endl;
			break;
		case EMessageType::S_ERROR:
			out << "ERROR: " << " (" << message << filename << ":" << line << ")" << std::endl;
			break;
		case EMessageType::S_FATAL_ERROR:
			out << "FATAL_ERROR: " << " (" << message << filename << ":" << line << ")" << std::endl;
			break;
		}
		out.close();
	}

	void Debug::Print(const std::string text) 
	{
		std::cout << text << std::endl;
	}


}