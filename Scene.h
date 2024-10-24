#pragma once

#include "GameObject.h"
#include"Camera.h"
#include <vector>

class Scene
{
public:
	std::vector<GameObject> objects;
	Camera camera;

	std::vector<Triangle2D> covertto2D() const;

	std::vector<Triangle3D> covertto2Dz() const;
	//returns triangles made from objects after translating to scenespace
	std::vector<Triangle3D> objectsToSceneSpace()const;

};

