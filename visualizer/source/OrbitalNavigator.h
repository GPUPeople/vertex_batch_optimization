


#ifndef INCLUDED_ORBITAL_NAVIGATOR
#define INCLUDED_ORBITAL_NAVIGATOR

#pragma once

#include <GL/platform/InputHandler.h>

#include <config/Database.h>

#include "Navigator.h"


class OrbitalNavigator : public Navigator, public virtual GL::platform::MouseInputHandler, public virtual GL::platform::KeyboardInputHandler
{
	math::float3 u;
	math::float3 v;
	math::float3 w;
	math::float3 position;

	math::int2 last_pos;
	unsigned int drag;

	float phi;
	float theta;
	float radius;
	math::float3 lookat;

	math::float3 initial_lookat;
	float initial_phi;
	float initial_theta;
	float initial_radius;

	void rotateH(float dphi);
	void rotateV(float dtheta);
	void zoom(float dr);
	void pan(float u, float v);
	void update();

	void buttonDown(GL::platform::Button button, int x, int y, GL::platform::Window*) override;
	void buttonUp(GL::platform::Button button, int x, int y, GL::platform::Window*) override;
	void mouseMove(int x, int y, GL::platform::Window*) override;
	void mouseWheel(int delta, GL::platform::Window*) override;

	void keyDown(GL::platform::Key key, GL::platform::Window*) override;
	void keyUp(GL::platform::Key key, GL::platform::Window*) override;

public:
	OrbitalNavigator(const config::Database& config, float phi, float theta, float radius, const math::float3& lookat = math::float3(0.0f, 0.0f, 0.0f));

	void reset()  override;
	void writeWorldToLocalTransform(math::affine_float4x4* M) const override;
	void writeLocalToWorldTransform(math::affine_float4x4* M) const override;
	void writePosition(math::float3* p) const override;

	void save(config::Database& config) const;
};

#endif  // INCLUDED_ORBITAL_NAVIGATOR
