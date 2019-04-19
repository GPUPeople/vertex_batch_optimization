


#version 450

#include <camera.glsl.h>


layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;
layout(location = 3) in uint v_invocations;
layout(location = 4) in uint v_invocations_simulated;

layout(location = 4) uniform vec3 mixcolor_inv0 = vec3(0.0f, 1.0f, 1.0f);
layout(location = 5) uniform vec3 mixcolor_inv1 = vec3(1.0f, 0.0f, 0.0f);
layout(location = 6) uniform vec3 mixcolor_sim0 = vec3(0.0f, 0.0f, 0.0f);
layout(location = 7) uniform vec3 mixcolor_sim1 = vec3(0.0f, 0.0f, 0.0f);
layout(location = 8) uniform vec3 mixcolor_diff0 = vec3(0.0f, 0.0f, 0.0f);
layout(location = 9) uniform vec3 mixcolor_diff1 = vec3(0.0f, 0.0f, 0.0f);

out vec3 normal;
out vec3 base_color;

void main()
{
	gl_Position = camera.PV * vec4(v_position, 1.0f);
	normal = (v_normal * camera.V_inv).xyz;

	if (v_invocations > 0U)
	{
		base_color = mix(mixcolor_inv0, mixcolor_inv1, v_invocations * 0.25f);
		base_color = base_color + mix(mixcolor_sim0, mixcolor_sim1, v_invocations_simulated * 0.25f);
		int diff = int(v_invocations) - int(v_invocations_simulated);
		if (diff > 0)
			//base_color = base_color + mixcolor_diff0 * diff;
			base_color = mix(vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), v_invocations * 0.2f);
		else
			base_color = base_color - mixcolor_diff1 * diff;
	}
	else
		base_color = vec3(0.0f, 0.0f, 0.0f);
}
