#pragma once
#include"Triangle4.h"
#include"Camera4.h"
#include<vector>
class GeometryProcessor
{
public:
	Triangle4 convertToCameraSpace(Triangle4 worldTriangle, Camera4 camera4)const;
	Triangle4 convertToClipSpace(Triangle4 cameraTriangle)const;
	std::vector<Triangle4> clipTriangle(Triangle4 clipTriangle)const;
	Triangle4 mapToScreen(Triangle4 triangle)const;
};

