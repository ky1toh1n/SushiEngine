#include "Debug.h"

namespace SushiEngine
{
	//Static fields
	int Debug::sObjectsConstructed = 0;
	int Debug::sConsoleFilter = 0
		//+ (int)EMessageType::S_INFO
		+ (int)EMessageType::S_WARNING 
		+ (int)EMessageType::S_ERROR 
		+ (int)EMessageType::S_FATAL_ERROR
		;
	uint8_t Debug::sTabLevel = 0;
	uint8_t Debug::sTabCap = 8;

	void Debug::Init()
	{
		std::ofstream out;
		// out.open("GameLog.txt", std::ios::app | std::ios::out);
		out.open("GameLog.txt", std::ios::out);
		out << std::endl;
		out.close();
	}

	void Debug::Log(const EMessageType MsgType, const std::string& pMessage, const std::string& pFilename, const int pLine) 
	{
		//Open file.
		std::ofstream out;
		out.open("GameLog.txt", std::ios::app | std::ios::out);

		//Indent message
		std::string message = pMessage;
		//Arbitraily cap the tab level
		if (sTabLevel >= sTabCap)
		{
			sTabLevel = sTabCap;
			Debug::Log(EMessageType::S_WARNING, "Tab level capped: "
				+ std::to_string(sTabCap), __FILENAME__, __LINE__);
		}
		//Actually indent the message
		for (uint8_t i = 0; i < sTabLevel; i++)
		{
			message = "\t" + message;
		}

		//Write to file.
		switch (MsgType) 
		{
		case EMessageType::S_INFO:
			out << "INFO: " << message << " (" << pFilename << ":" << pLine << ")" << std::endl;
			break;
		case EMessageType::S_WARNING:
			out << "WARNING: " << message << " (" << pFilename << ":" << pLine << ")" << std::endl;
			break;
		case EMessageType::S_ERROR:
			out << "ERROR: " << " (" << message << pFilename << ":" << pLine << ")" << std::endl;
			break;
		case EMessageType::S_FATAL_ERROR:
			out << "FATAL_ERROR: " << " (" << message << pFilename << ":" << pLine << ")" << std::endl;
			break;
		}

		//Close file.
		out.close();

		//If it matches any of the console filters, print to console as well.
		if (sConsoleFilter & (int)MsgType != 0)
		{
			Print(pMessage);
		}
	}

	void Debug::LogConstructor(const std::string& pMessage, const std::string& pFilename, const int pLine)
	{
		sObjectsConstructed++;
		Log(EMessageType::S_INFO, pMessage + "()", pFilename, pLine);
	}

	void Debug::LogDeconstructor(const std::string& pMessage, const std::string& pFilename, const int pLine)
	{
		sObjectsConstructed--;
		Log(EMessageType::S_INFO, "~" + pMessage + "()", pFilename, pLine);
	}

	void Debug::Print(const std::string pMessage)
	{
		std::cout << pMessage << std::endl;
	}

	int Debug::GetObjectsConstructed()
	{
		return sObjectsConstructed;
	}
}