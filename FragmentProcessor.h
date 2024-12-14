#pragma once
#include "WindowHandler.h"
#include<vector>
#include"Fragment.h"
class FragmentProcessor
{
private:
public:
	Uint32 getpixel(SDL_Surface* surface, int x, int y);
	WindowHandler& windowHandler;
	float* zbuffer;
	void drawFragments(const std::vector<Fragment>& fragments);
	void cleanZBuffer();
	FragmentProcessor(WindowHandler& windowHandler);
	~FragmentProcessor();
};

