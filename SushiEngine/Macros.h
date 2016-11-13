#ifndef MACROS_H
#define MACROS_H

#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>

namespace SushiEngine
{

#define vector(t) std::vector<t>

#define vec3 glm::vec3
#define quat glm::quat

#define NO_COPY_CONSTRUCTORS(classType) \
	classType(const classType&) = delete; \
	classType(classType&&) = delete; \
	classType& operator = (const classType&) = delete; \
	classType& operator = (classType&&) = delete;
}

#endif