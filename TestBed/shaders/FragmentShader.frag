#version 430

in vec4 myColor;
in vec2 texCoord;
out vec4 fColor;

uniform sampler2D texture;

uniform vec3 lightPosition;
uniform vec4 ambient_light;
uniform vec4 diffuse_light;

void main()
{
	// fColor = texture2D(texture, texCoord) * myColor;


	// temporary
	if (texCoord == 0) {
		fColor = myColor;
	} else {
		// fColor = vec4(1,0,0,1);
		// fColor = ambient_light;
		fColor =  texture2D(texture, texCoord) * ambient_light;

	}


};