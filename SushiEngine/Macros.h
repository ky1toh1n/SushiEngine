#ifndef MACROS_H
#define MACROS_H

// misc standard librariess
#include <string>
#include <iostream>
#include <typeinfo>
#include <type_traits>

// data structures
#include <vector>

// this party libraries
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>

namespace std
{
#include <cstdlib>
}

namespace SushiEngine
{
// macro for ensuring constructors arent implicitly created
#define NO_COPY_CONSTRUCTORS(classType) \
	classType(const classType&) = delete; \
	classType(classType&&) = delete; \
	classType& operator = (const classType&) = delete; \
	classType& operator = (classType&&) = delete;

// iostream macros
#define cout std::cout
#define cin std::cin
#define endl std::endl

	// primitives
	typedef std::string string;
	
	// data structures
	template<typename T>
	using vector = std::vector<T>;

	// glm structs that will be commonly used
	typedef glm::vec3 vec3;
	typedef glm::mat4 mat4;
	typedef glm::quat quat;
}

#endif