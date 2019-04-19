


#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA

#pragma once

#include <core/interface>

#include <math/matrix.h>


struct INTERFACE Camera
{
	struct UniformBuffer
	{
		alignas(16) math::affine_float4x4 V;
		alignas(16) math::affine_float4x4 V_inv;
		alignas(16) math::float4x4 P;
		alignas(16) math::float4x4 P_inv;
		alignas(16) math::float4x4 PV;
		alignas(16) math::float4x4 PV_inv;
		alignas(16) math::float3 position;
	};

	virtual void writeUniformBuffer(UniformBuffer* buffer, float aspect) const = 0;

protected:
	Camera() = default;
	Camera(const Camera&) = default;
	Camera& operator =(const Camera&) = default;
	~Camera() = default;
};

#endif  // INCLUDED_CAMERA
