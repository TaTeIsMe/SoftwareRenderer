#include "Scene.h"
#include<chrono>
#include<iostream>
extern int windowWidth;
extern int windowHeight;

std::vector<Triangle2D> Scene::covertto2D()const {
	std::vector<Triangle2D> sceneTriangles2D;
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects[i].GetShape().size(); j++)
		{
			Triangle2D projected = camera.triangle3Dto2D(
				objects[i].GetShape()[j]
				* objects[i].getRotation()
				+ objects[i].getPosition()
			);
			sceneTriangles2D.push_back(projected);
		}
	}
	return sceneTriangles2D;
}

std::vector<Triangle3D> Scene::covertto2Dz()const {
	std::vector<Triangle3D> sceneTriangles2Dz;
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects[i].GetShape().size(); j++)
		{
			//translate to world space
			Triangle3D toBeProjected = objects[i].GetShape()[j] * objects[i].getRotation() + objects[i].getPosition();
			toBeProjected.normal *= objects[i].getRotation();
			//tocameraspace
			toBeProjected = camera.convertToCameraSpace(toBeProjected);

			//backface culling
			if (Vector3::dotProduct(toBeProjected[0], toBeProjected.normal) >= 0)
			{
				goto skip;
			}

			//nearclipping please fix
			for (int k = 0; k < 3; k++)
			{
				//newrplane clipping change later
				if (toBeProjected[k].z < camera.getPlanez())
				{
					goto skip;
				};
			}
			//cast onto screen
			toBeProjected = camera.triangle3Dto2Dz(toBeProjected);
			//frustrum clipping oh god please fix later!!
			for (int k = 0; k < 3; k++)
			{
				if (abs(toBeProjected[k].x) > windowWidth/2. || abs(toBeProjected[k].y) > windowHeight / 2.)
				{
					camera.clipTriangleToSides2D(toBeProjected,sceneTriangles2Dz);
					goto skip;
				}
			}
			sceneTriangles2Dz.push_back(toBeProjected);
		skip:;
		}
	}
	return sceneTriangles2Dz;
}

std::vector<Triangle3D> Scene::objectsToSceneSpace() const
{
	std::vector<Triangle3D> temp;
	for (int i = 0; i < objects.size(); i++)
	{
		for (int k = 0; k < objects[i].GetShape().size(); k++)
		{
			temp.push_back(objects[i].GetShape()[k] * objects[i].getRotation() + objects[i].getPosition());
			temp.back().normal *= objects[i].getRotation();
		}
	}
	return temp;
}
