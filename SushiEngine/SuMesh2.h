#ifndef SU_MESH_2_H
#define SU_MESH_2_H


#include "Debug.h"

#include "GL\glew.h"

// SuMesh Class a class that holds the vertex data and default color data for each vertex. Ideally, each mesh will be unique and will only be loaded once each.

// TODO: Current mplementation uses 2 separate buffers for the vertex data and the default color data. Might want to use Sub Buffers instead.
namespace SushiEngine 
{

	class SuMesh2
	{
	public:
		SuMesh2();
		~SuMesh2();

		SuMesh2(const SuMesh2&) = delete;
		SuMesh2(SuMesh2&&) = delete;
		SuMesh2& operator = (const SuMesh2&) = delete;
		SuMesh2& operator = (SuMesh2&&) = delete;

		// @params: The vertex data to be used
		// @params: The default color of the vertex points, which may or may not be used by the shaders
		// @params: The number of vertices in the vertexData which will be used for rendering

		// TODO: Have a dynamic implementation of _numVerts, unsure on how to do this
		// TODO: Have changes in rendering type loaded too. Such as a variation btwn GL_TRIANGLES, GL_QUADS, GL_LINES, etc.
		bool LoadMesh(const GLfloat* _vertexData, const GLfloat* _colorData, const GLuint _numVerts);

		// TODO: Decide whether to keep a render implementation here for a SuGameObject to use for rendering, such that GameObject->Render()----> Mesh->Render()
		//											OR
		// Have the game object retrieve the value from the mesh and then draw that in its own class
		void Use();

	private:
		GLuint vertexBuffer[2]; // A size of 2 so that we can keep track of a default color value too
		GLuint numVerts;
	};

}
#endif;

