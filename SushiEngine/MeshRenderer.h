/* Stores a handle to the data needed to render a Mesh. */
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H
/* SushiEngine */
#include "Component.h"
#include "Macros.h"
#include "ModelManager.h"
/* ---- */
namespace SushiEngine
{
	class MeshRenderer : public Component
	{
	public:
		/* Constructor */
		MeshRenderer(const SuGameObject * fGameObject, const string fFilePath);
		~MeshRenderer();

		/* Instance methods */
		const GLuint* GetModelID();

	private:
		/* Instance fields */
		const GLuint* mModelID;

		/* Instance methods */
		void BindBuffer();
	};
}
#endif