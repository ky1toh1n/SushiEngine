#include "Camera.h"

namespace SushiEngine {
	Camera::Camera(glm::vec3 position, glm::vec3 up, float angleX, float angleY) : pos(position), angleX(angleX), angleY(angleY), up(up)
	{
		computeLookAt();
	}


	Camera::~Camera()
	{
	}

	void Camera::translate(float x, float y) {
		//Forwards movement: 
		glm::vec3 forwardAxis(lookAt * -y);

		//Sideways movement: cross product
		glm::vec3 sidewaysAxis(glm::normalize(glm::cross(lookAt, up)) * -x);

		//Add to camera position
		pos += sidewaysAxis + forwardAxis;

	}

	void Camera::rotate(float x, float y) {
		angleX += x;
		angleY += y;
		computeLookAt();
	}

	void Camera::computeLookAt() {
		//Look at; uses two circles (along XZ and YZ axis) to find the proper rotation
		lookAt = glm::vec3(
			glm::sin(angleX),
			glm::sin(angleY),
			-glm::cos(angleX) * glm::cos(angleY));
	}

	glm::mat4 Camera::getMatrix() {
		return glm::lookAt(pos, pos + lookAt, up);
	}
}