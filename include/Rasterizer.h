#pragma once
#include "WindowHandler.h"
#include <vector>
#include "Triangle2D.h"
#include "Triangle3.h"
extern int windowWidth;
class Rasterizer
{
	WindowHandler& windowHandler;
	float* zbuffer;
	void drawScanline(struct LineVars line1,struct LineVars line2,struct gradients gra, float dxz, Triangle3 triangle);
	void drawTexuredPointZ(int y, int x,float uprim,float vprim,float zprim,float z, Triangle3 triangle, Uint32& data, SDL_Color& color);
public:
	void drawTrianglezWire(Triangle3 triangle) const;
	void drawTriangle(Triangle2D triangle, Uint8 r, Uint8 g, Uint8 b) const;
	void drawTrianglez(Triangle3& triangle);
	Rasterizer(WindowHandler& windowHandler);
	~Rasterizer();
	void cleanzbuffer();
	SDL_Color getTextureColor(float uprim, float vprim, float zprim, Uint32& data, SDL_Color& color);
	void drawLine(Vector2 begginingPoint, Vector2 endingPoint , Uint8 r, Uint8 g, Uint8 b) const;
	void drawTrianglezBBox(Triangle3 triangle);
	void drawScene(std::vector<Triangle2D> triangles)const;
	void drawScenez( std::vector<Triangle3>& triangles);
	void drawScenezBBox(const std::vector<Triangle3>& triangles);
	void drawScenezWire(const std::vector<Triangle3>& triangles) const;
};

