#include "SuTexture.h"
#include <IL/il.h>

namespace SushiEngine {

	void SuTexture::freeTexture() {
		//Delete texture
		if (mTextureID != 0)
		{
			glDeleteTextures(1, &mTextureID);
			mTextureID = 0;
		}

		mTextureWidth = 0;
		mTextureHeight = 0;
	}

	bool SuTexture::loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height) {
		//Free texture if it exists
		freeTexture();

		//Get texture dimensions
		mTextureWidth = width;
		mTextureHeight = height;

		//Generate texture ID
		glGenTextures(1, &mTextureID);

		//Bind texture ID
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		//Generate texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		//Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//Unbind texture
		glBindTexture(GL_TEXTURE_2D, NULL);

		//Check for error
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error loading texture from %p pixels! %s\n", pixels, gluErrorString(error));
			return false;
		}

		return true;
	}

	bool SuTexture::loadTextureFromFile(std::string path)
	{
		//Texture loading success
		bool textureLoaded = false;

		//Generate and set current image ID
		ILuint imgID = 0;
		ilGenImages(1, &imgID);
		ilBindImage(imgID);

		//Load image
		ILboolean success = ilLoadImage(path.c_str());

		//Image loaded successfully
		if (success == IL_TRUE)
		{
			//Convert image to RGBA
			success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
			if (success == IL_TRUE)
			{
				//Create texture from file pixels
				textureLoaded = loadTextureFromPixels32((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
			}

			//Delete file from memory
			ilDeleteImages(1, &imgID);
		}

		//Report error
		if (!textureLoaded)
		{
			printf("Unable to load %s\n", path.c_str());
		}

		return textureLoaded;
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