
#version 450



layout(location = 0) in VertexData{
	vec3 normal;
	vec3 v_color;
} v_in;

layout(location = 0) out vec4 color;

void main()
{
	vec3 n = normalize(v_in.normal);
	//uvec2 t = clock2x32ARB();
	//invo_details[gl_PrimitiveID] = uvec4(gl_SMIDNV, gl_WarpIDNV, t.y, activeThreadsNV());

	color = vec4(-n.z*v_in.v_color, 1.0f);
	//for (int i = 0; i < 100000; ++i)
	//	color.xyz = color.xyz * color.zxy;

	//invo_details[gl_PrimitiveID] = uvec4(0,1,2,3);
}
