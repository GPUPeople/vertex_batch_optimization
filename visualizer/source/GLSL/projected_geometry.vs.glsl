


#version 450


layout(location = 0) in vec4 v_position;
layout(location = 1) in vec3 v_texcoord;
layout(location = 2) in vec3 v_normal;

out vec3 normal;

void main()
{
	gl_Position = v_position;
	normal = v_normal;
}
