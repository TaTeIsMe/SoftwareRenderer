#pragma once
#include "Triangle4.h"
#include "Camera.h"
#include "RigidBody.h"
struct Camera4
{
	RigidBody rigidBody;
public:
	Camera4();
	explicit Camera4(const class Camera&);
};

