#include "FragmentProcessor.h"

extern int windowHeight;
extern int windowWidth;

Uint32 FragmentProcessor::getpixel(SDL_Surface* surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16*)p;
		break;

	case 3:
		return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32*)p;
		break;

	default:
		return 0;
	}
}


void FragmentProcessor::drawFragments(const std::vector<Fragment>& fragments)
{
	Uint32 data;
	SDL_Color color;
	for (int i = 0; i < fragments.size(); i++)
	{
		const Fragment& fragment = fragments[i];
		if (abs(fragment.y) < windowHeight / 2. && abs(fragment.x) < windowWidth / 2.) {
			unsigned int offset = (windowWidth * (-fragment.y + windowHeight / 2.)) + (fragment.x + windowWidth / 2.);
			if (fragment.z < zbuffer[offset])
			{
				unsigned int u = fragment.uprim * fragment.texture->h / fragment.wprim;
				unsigned int v = fragment.vprim * fragment.texture->w / fragment.wprim;

				if (u < fragment.texture->w && v < fragment.texture->h)
					data = getpixel(fragment.texture, u, v);
				else
					data = getpixel(fragment.texture, 1, 1);
				SDL_GetRGB(data, fragment.texture->format, &color.r, &color.g, &color.b);
				zbuffer[offset] = fragment.z;
				windowHandler.drawPoint(Vector2(fragment.x, fragment.y), color.r, color.g, color.b, 0xFF);
			}
		}
	}
}

void FragmentProcessor::cleanZBuffer()
{
	for (int i = 0; i < windowHeight * windowWidth; i++)
	{
		zbuffer[i] = INFINITY;
	}
}

FragmentProcessor::FragmentProcessor(WindowHandler& windowHandler) :windowHandler(windowHandler)
{
    zbuffer = new float[windowHeight * windowWidth];
    for (int i = 0; i < windowHeight * windowWidth; i++)
    {
        zbuffer[i] = INFINITY;
    }
}

FragmentProcessor::~FragmentProcessor() {
    delete[] zbuffer;
}