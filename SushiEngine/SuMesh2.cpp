#include "SuMesh2.h"

namespace SushiEngine
{

	SuMesh2::SuMesh2()
	{
	}


	SuMesh2::~SuMesh2()
	{
	}


	// TODO: Link this to a resource manager such that when a model data is read, it will read the model vertex data and store it here.
	/*
	prototype

	Model a = Assimp.LoadModel("apple.ext");
	_vertexData = a.GetVertexData();

	SuMesh* mesh = new SuMesh();
	mesh->LoadMesh(_vertexData);
	
	*/
	bool SuMesh2::LoadMesh(const GLfloat* _vertexData, const GLfloat* _colorData, const GLuint _numVerts) 
	{
		glGenBuffers(2, vertexBuffer); // Create buffer binding point
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]); // bind current buffer to binding point

		// Sidenote: Apparently there's no way to get the size of an array a pointer is pointing to.. so I just multiplied it by .. this.. need an alternative
		glBufferData(GL_ARRAY_BUFFER, sizeof(_vertexData) * _numVerts * 3, _vertexData, GL_STATIC_DRAW); // send data to GPU.. this is static because we will only need to load this type of mesh once.. hopefully

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_colorData) * _numVerts * 3, _colorData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind buffer to prevent accidental access

		numVerts = _numVerts;
		return vertexBuffer ? true : false;
	}

	void SuMesh2::Use() 
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]); // Switch buffer binding point
		glEnableVertexAttribArray(0); // Set pointer '0' to start of buffer attrib
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Describe how data is read

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// glDrawArrays(GL_QUADS, 0, numVerts);
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind buffer to prevent accidental access
		// Debug::Print("Rendering...");
	}
}