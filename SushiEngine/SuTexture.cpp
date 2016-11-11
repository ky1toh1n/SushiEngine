#include "SuTexture.h"
#include <IL/il.h>

namespace SushiEngine {

	SuTexture::SuTexture() {
	}

	SuTexture::~SuTexture() {

	}

	bool SuTexture::LoadTexture(GLuint* _texData, GLfloat* _UVData, GLuint _width, GLuint _height) {
		glGenTextures(1, &mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		//Generate texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _texData);

		//Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// UV Coords
		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_UVData) * 16 * 2, _UVData, GL_STATIC_DRAW);

		// Unbind
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (mTextureID && uvBuffer) return true;

		return false;
	}

	void SuTexture::Use() {
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		// Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLuint SuTexture::getTextureID() {
		return mTextureID;
	}

	GLuint SuTexture::textureWidth() {
		return mTextureWidth;
	}

	GLuint SuTexture::textureHeight() {
		return mTextureHeight;
	}
}