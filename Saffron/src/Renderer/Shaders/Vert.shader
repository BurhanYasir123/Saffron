#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in float texbool;

out vec3 fragColor;
out vec2 TexCoords;
out float TexBool;

uniform float uAspectFix_X;
uniform mat4 VP;

void main()
{
	vec4 vert = VP * vec4(pos, 1.0);

	vert.x *= uAspectFix_X;
	
	gl_Position = vert;
	fragColor = color;
	TexCoords = texcoord;
	TexBool = texbool;
}