#include "Camera.h"

namespace SushiEngine 
{
	Camera::Camera(glm::vec3 pPosition, glm::vec3 pUp, float pAngleX, float pAngleY)
		: mPosition(pPosition), mAngleX(pAngleX), mAngleY(pAngleY), mUp(pUp)
	{
		computeLookAt();
	}


	Camera::~Camera()
	{
	}

	void Camera::translate(float x, float y) 
	{
		//Forwards movement: 
		glm::vec3 forwardAxis(mLookAt * -y);

		//Sideways movement: cross product
		glm::vec3 sidewaysAxis(glm::normalize(glm::cross(mLookAt, mUp)) * -x);

		//Add to camera position
		mPosition += sidewaysAxis + forwardAxis;

	}

	void Camera::rotate(float x, float y) 
	{
		mAngleX += x;
		mAngleY += y;
		computeLookAt();
	}

	//Calculates the 'Look At' vector
	void Camera::computeLookAt() 
	{
		//Look at; uses two circles (along XZ and YZ axis) to find the proper rotation
		mLookAt = glm::vec3(
			glm::sin(mAngleX),
			glm::sin(mAngleY),
			-glm::cos(mAngleX) * glm::cos(mAngleY));
	}

	glm::mat4 Camera::getMatrix() 
	{
		return glm::lookAt(mPosition, mPosition + mLookAt, mUp);
	}
}