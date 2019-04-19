


#version 450

#include <camera.glsl.h>


layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;

out vec3 normal;

void main()
{
	gl_Position = camera.PV * vec4(v_position, 1.0f);
	normal = (v_normal * camera.V_inv).xyz;
}
