/* A first peron fly-through camera. 
 Currently translates along the XY plane, and rotates along Y and Z axis*/
#ifndef CAMERA_H
#define CAMERA_H
/* Third Party */
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
/* ---- */
namespace SushiEngine
{
	class Camera
	{
	public:
		/* Constructor */
		Camera(glm::vec3 pPosition, glm::vec3 pUp, float pAngleX=0, float pAngleY=0);
		~Camera();

		/* Instance methods */
		void translate(float x, float y);
		void rotate(float x, float y);
		glm::mat4 getMatrix();
	private:
		/* Instance fields */
		glm::vec3 mPosition;
		float mAngleX;
		float mAngleY;
		glm::vec3 mLookAt;
		glm::vec3 mUp;

		/* Instance methods */
		void computeLookAt();
	};
}
#endif
