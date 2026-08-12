#pragma once
#include"Fragment.h"
#include<vector>
#include"Triangle4.h"
class RasterizationProcessor
{
private:
	bool incrementLine(struct LineVars& line,const struct gradients& gra, float dyz, float dxz, SDL_Surface* texture, std::vector<Fragment>& fragments);
	void drawScanLine(const struct LineVars& line1, const struct LineVars& line2, const struct gradients& gra, float dxz, SDL_Surface* texture, std::vector<Fragment>& fragments);
public:
	std::vector<Fragment>& rasterizeTriangle(Triangle4& triangle, std::vector<Fragment>& fragments);
};

