#pragma once
#include "Triangle4.h"
#include "Camera.h"
#include "RigidBody.h"
struct Camera4
{
	RigidBody inverse;
	RigidBody rigidBody;
	Camera4();
	explicit Camera4(const class Camera&);
	RigidBody calculateInverse();
};

