#pragma once
#include "WindowHandler.h"
#include<vector>
#include"Fragment.h"
class FragmentProcessor
{
private:
	float* zbuffer;
	WindowHandler& windowHandler;
	Uint32 getpixel(SDL_Surface* surface, int x, int y);
public:
	void drawFragments(const std::vector<Fragment>& fragments);
	void cleanZBuffer();
	FragmentProcessor(WindowHandler& windowHandler);
	~FragmentProcessor();
};

