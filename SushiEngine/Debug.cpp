#include "Debug.h"

namespace SushiEngine {

	void Debug::Init() {
		std::ofstream out;
		// out.open("GameLog.txt", std::ios::app | std::ios::out);
		out.open("GameLog.txt", std::ios::out);
		out << std::endl;
		out.close();
	}

	void Debug::Log(const EMessageType MsgType, const std::string& message, const std::string& filename, const int line) {
		std::ofstream out;
		out.open("GameLog.txt", std::ios::app | std::ios::out);
		// out.open("GameLog.txt", std::ios::out);

		switch (MsgType) {
		case EMessageType::INFO:
			out << "INFO: " << message << " (" << filename << ":" << line << ")" << std::endl;
			break;
		case EMessageType::WARNING:
			out << "WARNING: " << message << " (" << filename << ":" << line << ")" << std::endl;
			break;
		case EMessageType::ERROR:
			out << "ERROR: " << " (" << message << filename << ":" << line << ")" << std::endl;
			break;
		case EMessageType::FATAL_ERROR:
			out << "FATAL_ERROR: " << " (" << message << filename << ":" << line << ")" << std::endl;
			break;
		}
		out.close();
	}

	void Debug::Print(const std::string text) {
		std::cout << text << std::endl;
	}


}