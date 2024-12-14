#pragma once
#include"Pixel.h"
#include<vector>
#include"Triangle4.h"
class RasterizationProcessor
{
public:
	std::vector<Pixel> rasterizeTriangle(Triangle4& triangle, std::vector<Pixel>& pixels);
};

