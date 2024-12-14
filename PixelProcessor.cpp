#include "PixelProcessor.h"

extern int windowHeight;
extern int windowWidth;

Uint32 PixelProcessor::getpixel(SDL_Surface* surface, int x, int y)
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


void PixelProcessor::drawPixels(const std::vector<Pixel>& pixels)
{
	Uint32 data;
	SDL_Color color;
	for (int i = 0; i < pixels.size(); i++)
	{
		const Pixel& pixel = pixels[i];
		if (abs(pixel.y) < windowHeight / 2. && abs(pixel.x) < windowWidth / 2.) {
			unsigned int offset = (windowWidth * (-pixel.y + windowHeight / 2.)) + (pixel.x + windowWidth / 2.);
			if (pixel.z < zbuffer[offset])
			{
				unsigned int u = pixel.uprim * pixel.texture->h / pixel.wprim;
				unsigned int v = pixel.vprim * pixel.texture->w / pixel.wprim;

				if (u < pixel.texture->w && v < pixel.texture->h)
					data = getpixel(pixel.texture, u, v);
				else
					data = getpixel(pixel.texture, 1, 1);
				SDL_GetRGB(data, pixel.texture->format, &color.r, &color.g, &color.b);
				zbuffer[offset] = pixel.z;
				windowHandler.drawPoint(Vector2(pixel.x, pixel.y), color.r, color.g, color.b, 0xFF);
			}
		}
	}
}

void PixelProcessor::cleanZBuffer()
{
	for (int i = 0; i < windowHeight * windowWidth; i++)
	{
		zbuffer[i] = INFINITY;
	}
}

PixelProcessor::PixelProcessor(WindowHandler& windowHandler) :windowHandler(windowHandler)
{
    zbuffer = new float[windowHeight * windowWidth];
    for (int i = 0; i < windowHeight * windowWidth; i++)
    {
        zbuffer[i] = INFINITY;
    }
}

PixelProcessor::~PixelProcessor() {
    delete[] zbuffer;
}