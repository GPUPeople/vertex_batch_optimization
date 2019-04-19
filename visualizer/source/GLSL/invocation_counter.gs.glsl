
#version 450
#extension GL_NV_geometry_shader_passthrough : require
#extension GL_NV_shader_thread_group : enable
#extension GL_ARB_shader_clock : enable

layout(triangles) in;

layout(passthrough) in gl_PerVertex{
	vec4 gl_Position;
} gl_in[];

// Declare "Inputs" with "passthrough" to automatically copy members.

layout(passthrough, location = 0) in VertexData {
	vec3 normal;
	vec3 v_color;
} v_in[];

layout(location = 2) in InfoVertexData{
	uvec4 info;
} vertexInfo_in[];


layout(std430, binding = 2) buffer InfoTimeInfo
{
	uvec4 invo_details[];
};

void main()
{
	uvec2 t = clock2x32ARB();
	//invo_details[maxinvopervertex*gl_VertexID + invo_num] = uvec4(gl_SMIDNV, gl_WarpIDNV, t.x, t.y);
	//invo_details[gl_PrimitiveIDIn] = uvec4(gl_SMIDNV, gl_WarpIDNV, t.x, t.y);

	invo_details[gl_PrimitiveIDIn] = vertexInfo_in[0].info;
}