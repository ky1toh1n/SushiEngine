#include "MeshRenderer.h"

namespace SushiEngine
{
	MeshRenderer::MeshRenderer(const SuGameObject * fGameObject, const string fFilePath) : Component(fGameObject)
	{
		mModelID = ModelManager::LoadModel(fFilePath);
		BindBuffer();
	}


	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::BindBuffer()
	{
		GLuint renderId = *mModelID;
		//cout << renderId << endl;
		glBindBuffer(GL_ARRAY_BUFFER, renderId);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	const GLuint* MeshRenderer::GetModelID()
	{
		return mModelID;
	}
}