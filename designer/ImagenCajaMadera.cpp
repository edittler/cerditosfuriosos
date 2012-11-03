#include "ImagenCajaMadera.h"

ImagenCajaMadera::ImagenCajaMadera(int x, int y) :
	ImagenPosicionable(RUTA_CAJA_MADERA)
{
	this->x = x;
	this->y = y;
}

ImagenCajaMadera::~ImagenCajaMadera() {}
