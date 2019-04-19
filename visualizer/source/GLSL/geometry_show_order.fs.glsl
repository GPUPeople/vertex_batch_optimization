


#version 450

layout(location = 0) uniform float primitive_id_scale;

in vec3 normal;

layout(location = 0) out vec4 color;

void main()
{
	vec3 n = normalize(normal);

	color = vec4(-n.zzz * vec3(gl_PrimitiveID * primitive_id_scale), 1.0f);
}
