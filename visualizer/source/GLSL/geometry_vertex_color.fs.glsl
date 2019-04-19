


#version 450


in vec3 normal;
in vec3 base_color;

layout(location = 0) out vec4 color;

layout(location = 2) uniform ivec2 selected_primitive_range = ivec2(-1, -1);

void main()
{
	vec3 n = normalize(normal);
	vec3 usecolor = base_color;
	if (selected_primitive_range.x != selected_primitive_range.y && (gl_PrimitiveID < selected_primitive_range.x || gl_PrimitiveID >= selected_primitive_range.y))
	{
		usecolor = vec3(0.9, 0.9, 0.9);
	}
	color = vec4(usecolor * -n.zzz, 1.0f);
}
