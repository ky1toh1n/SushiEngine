#version 430
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vTexCoord;
layout(location = 3) in vec3 vNormal;

uniform mat4 model_matrix;
uniform mat4 camera_matrix;
uniform mat4 projection_matrix;

out vec4 myColor;
out vec2 texCoord;

void main()
{
	myColor = vColor;
	gl_Position = projection_matrix * camera_matrix * model_matrix * vPosition;
	texCoord = vTexCoord;
}
