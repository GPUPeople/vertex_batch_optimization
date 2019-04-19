


#ifndef INCLUDED_NAVIGATOR
#define INCLUDED_NAVIGATOR

#pragma once

#include <core/interface>

#include <math/matrix.h>


struct INTERFACE Navigator
{
	virtual void reset() = 0;
	virtual void writeWorldToLocalTransform(math::affine_float4x4* M) const = 0;
	virtual void writeLocalToWorldTransform(math::affine_float4x4* M) const = 0;
	virtual void writePosition(math::float3* p) const = 0;

protected:
	Navigator() = default;
	Navigator(const Navigator&) = default;
	Navigator& operator =(const Navigator&) = default;
	~Navigator() = default;
};

#endif  // INCLUDED_NAVIGATOR
