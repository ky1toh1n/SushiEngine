#ifndef CAMERA_H
#define CAMERA_H

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

namespace SushiEngine
{
	class Camera
	{
	public:
		Camera(glm::vec3 position, glm::vec3 up, float angleX=0, float angleY=0);
		~Camera();

		void translate(float x, float y);
		void rotate(float x, float y);
		glm::mat4 getMatrix();

	private:
		glm::vec3 pos;
		float angleX;
		float angleY;
		glm::vec3 lookAt;
		glm::vec3 up;

		void computeLookAt();
	};
}
#endif
