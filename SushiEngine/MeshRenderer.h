#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H
#include "Component.h"
#include "Macros.h"
#include "ModelManager.h"

namespace SushiEngine
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer(const SuGameObject * fGameObject, const string fFilePath);
		~MeshRenderer();

		const GLuint* GetModelID();

	private:
		void BindBuffer();
		const GLuint* mModelID;
	};
}
#endif