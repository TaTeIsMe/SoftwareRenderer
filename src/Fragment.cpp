#include "Fragment.h"

Fragment::Fragment(int x, int y, float uprim, float vprim, float wprim, float z, SDL_Surface* texture):
	x(x),y(y),z(z),
	uprim(uprim), vprim(vprim), wprim(wprim),
	texture(texture)
{
}
