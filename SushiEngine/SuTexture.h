#ifndef SU_TEXTURE_H
#define SU_TEXTURE_H

#include <GL/glew.h>
#include <stdio.h>

namespace SushiEngine {

	class SuTexture {

	public:
		SuTexture();
		~SuTexture();

		SuTexture(const SuTexture&) = delete;
		SuTexture(SuTexture&&) = delete;
		SuTexture& operator = (const SuTexture&) = delete;
		SuTexture& operator = (SuTexture&&) = delete;

		bool LoadTexture(GLuint* _texData, GLfloat* _UV, GLuint _width, GLuint _height);
		void Use();

		// Accessors
		GLuint getTextureID();
		GLuint textureWidth();
		GLuint textureHeight();


	private:
		//Texture name
		GLuint mTextureID;
		GLuint uvBuffer;

		//Texture dimensions
		GLuint mTextureWidth;
		GLuint mTextureHeight;

	};
}
#endif
