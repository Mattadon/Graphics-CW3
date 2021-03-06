#version 400 core
layout (location = 0) in vec3 position;

uniform mat4 lightSpace;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = lightSpace * modelMatrix * vec4(position, 1.0f);
}