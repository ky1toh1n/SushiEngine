#ifndef SU_TEXTURE_H
#define SU_TEXTURE_H

#include <GL/glew.h>
#include <stdio.h>
#include <string>

namespace SushiEngine {

	class SuTexture {

	public:
		SuTexture() {};
		~SuTexture() {};

		SuTexture(const SuTexture&) = delete;
		SuTexture(SuTexture&&) = delete;
		SuTexture& operator = (const SuTexture&) = delete;
		SuTexture& operator = (SuTexture&&) = delete;

		void freeTexture();

		bool loadTextureFromFile(std::string path);

		// Creates a texture from the given pixels
		bool loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height);

		// Accessors
		GLuint getTextureID();
		GLuint textureWidth();
		GLuint textureHeight();


	private:
		//Texture name
		GLuint mTextureID;

		//Texture dimensions
		GLuint mTextureWidth;
		GLuint mTextureHeight;

	};
}
#endif
