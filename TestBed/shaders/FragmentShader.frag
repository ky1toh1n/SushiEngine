#version 430

in vec4 myColor;
in vec2 texCoord;
out vec4 fColor;

uniform sampler2D texture;

uniform vec4 ambient_light;
uniform vec4 diffuse_light;

in vec3 fNormal;
in vec3 fLight;

void main()
{
	// fColor = texture2D(texture, texCoord) * myColor;


	// temporary
	if (texCoord == 0) {
		fColor = myColor;
	} else {
		// fColor = vec4(1,0,0,1);
		// fColor = ambient_light;

		vec3 N = normalize(fNormal);
		vec3 L = normalize(fLight);

		float Kdiffuse = max(dot(L, N), 0.0);
		vec4 diffuse = Kdiffuse*diffuse_light;
    

		fColor =  texture2D(texture, texCoord) * (ambient_light + diffuse);

	}


}