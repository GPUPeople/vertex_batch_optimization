


#version 450


layout(location = 1, binding = 1) uniform samplerBuffer batch_color;
layout(location = 2) uniform ivec2 selected_primitive_range = ivec2(-1, -1);

in vec3 normal;

layout(location = 0) out vec4 color;

void main()
{
	vec3 n = normalize(normal);

	vec4 base_color = texelFetch(batch_color, gl_PrimitiveID);
	if (selected_primitive_range.x != selected_primitive_range.y && (gl_PrimitiveID < selected_primitive_range.x || gl_PrimitiveID >= selected_primitive_range.y))
	{
		base_color = vec4(0.9, 0.9, 0.9, 1.0);
	}
	color = vec4(-n.zzz * base_color.rgb, 1.0);
}
