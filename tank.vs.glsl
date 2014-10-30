//#version 330 core
#version 140
#extension GL_ARB_explicit_attrib_location : require

layout (location = 0) in vec4 vPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 vColor;

out vec4 color;

void main () {
	color = vColor;
	gl_Position = projection * view * model * vPosition;
}

