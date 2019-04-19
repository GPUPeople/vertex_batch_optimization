


#version 450


in vec3 normal;

layout(location = 0) out vec4 color;

void main()
{
	vec3 n = normalize(normal);

	color = vec4(-n.zzz, 1.0f);
}
