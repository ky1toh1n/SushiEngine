#version 430

in vec4 myColor;
in vec2 texCoord;
out vec4 fColor;

uniform sampler2D texture;

void main()
{
	// fColor = texture2D(texture, texCoord) * myColor;


	// temporary
	if (texCoord == 0) {
		fColor = myColor;
	} else {
		fColor =  texture2D(texture, texCoord);
	}


};