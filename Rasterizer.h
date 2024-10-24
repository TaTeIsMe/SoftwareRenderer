#pragma once
#include "WindowHandler.h"
#include <vector>
#include "Triangle2D.h"
#include "Triangle3D.h"

extern int windowWidth;
class Rasterizer
{
	WindowHandler& windowHandler;
	float* zbuffer;
	void drawScanline(struct LineVars line1,struct LineVars line2,struct gradients gra, float dxz, Triangle3D triangle);
	void drawTexuredPointZ(const int& y, const int& x,const float& uprim,const float& vprim,const float& zprim,const float& z, Triangle3D triangle, Uint32& data, SDL_Color& color);
	void drawTrianglez(Triangle3D triangle);
	void drawTrianglezWire(Triangle3D triangle) const;
	void drawTriangle(Triangle2D triangle) const;
public:
	Rasterizer(WindowHandler& windowHandler);
	~Rasterizer();
	void cleanzbuffer();
	SDL_Color getTextureColor(const float& uprim, const float& vprim, const float& zprim, Uint32& data, SDL_Color& color);
	void drawLine(Vector2 begginingPoint, Vector2 endingPoint) const;
	void drawTrianglezBBox(Triangle3D triangle);
	void drawScene(std::vector<Triangle2D> triangles)const;
	void drawScenez(const std::vector<Triangle3D>& triangles);
	void drawScenezBBox(const std::vector<Triangle3D>& triangles);
	void drawScenezWire(const std::vector<Triangle3D>& triangles) const;
};
