#include "Pixel.h"

Pixel::Pixel(int x, int y, float uprim, float vprim, float wprim, float w, SDL_Surface* texture):
	x(x),y(y),w(w),
	uprim(uprim), vprim(vprim), wprim(wprim),
	texture(texture)
{
}
