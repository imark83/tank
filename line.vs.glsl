//#version 330 core
#version 140
#extension GL_ARB_explicit_attrib_location : require

layout (location = 0) in vec4 vPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main () {
	gl_Position = projection * view * model * vPosition;
}
