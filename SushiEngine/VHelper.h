#ifndef V_HELPER_H
#define V_HELPER_H
#include "Debug.h"

#define HANDLE_VK_RESULT(vkCreateMethod) \
{	\
	VkResult result = vkCreateMethod;	\
	if (result != VK_SUCCESS) { \
		const std::string message  = "Bad VkResult Returned: " + std::to_string(result); \
		Debug::Log(EMessageType::S_FATAL_ERROR, message + ", ", __FILENAME__, __LINE__); \
		Debug::Print(message); \
	} \
}	\

#endif