#pragma once
#include"Fragment.h"
#include<vector>
#include"Triangle4.h"
class RasterizationProcessor
{
public:
	std::vector<Fragment> rasterizeTriangle(Triangle4& triangle, std::vector<Fragment>& fragments);
};

