#include "Camera4.h"

Camera4::Camera4(const Camera& camera): rigidBody(camera.getRotation(),camera.getPosition())
{

}

