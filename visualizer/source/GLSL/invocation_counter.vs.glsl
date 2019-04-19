
#version 450
#extension GL_NV_shader_thread_group : enable
#extension GL_ARB_shader_clock : enable

#include <camera.glsl.h>

layout(location = 1, binding = 1) uniform samplerBuffer colors;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;

layout(std430, binding = 3) buffer invocounter
{
	int invo_data[];
};



//layout(location = 2) uniform uint maxinvopervertex = 6;
//layout(std430, binding = 4) buffer invoinfo
//{
//	uvec4 invo_details[];
//};

layout(location = 0) out VertexData {
	vec3 normal;
	vec3 v_color;
} vertex;

layout(location = 2) out InfoVertexData{
	uvec4 info;
} vertexInfo;

void main()
{
	gl_Position = camera.PV * vec4(v_position, 1.0f);
	vertex.normal = (v_normal * camera.V_inv).xyz;

	int invo_num = atomicAdd(invo_data[gl_VertexID], 1);
	uvec2 t = clock2x32ARB();
	//invo_details[maxinvopervertex*gl_VertexID + invo_num] = uvec4(gl_SMIDNV, gl_WarpIDNV, t.x, t.y);
	vertexInfo.info = uvec4(gl_SMIDNV, gl_WarpIDNV, t.y, bitCount(activeThreadsNV()));
	
	//invo_details[gl_VertexID / 32] = invocation_info;
	
	uint actives = bitCount(activeThreadsNV());
	int id = int(gl_WarpsPerSMNV * gl_SMIDNV + gl_WarpIDNV);
	vec4 base_color = texelFetch(colors, id);
	
	//for (int i = 0; i < 1024; ++i)
	//{
	//	vec4 base_color2 = texelFetch(colors, (id+i)%1024);
	//	if (base_color2.w > base_color.w)
	//		base_color = base_color2;
	//}
	vertex.v_color = base_color.xyz * float(actives)/32.0f;


	//v_color = vec3(0.9, 0.9, 0.9);
}
