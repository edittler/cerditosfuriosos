#include "ImagenCajaMetal.h"

ImagenCajaMetal::ImagenCajaMetal(int x, int y) :
	ImagenPosicionable(RUTA_CAJA_METAL)
{
	this->x = x;
	this->y = y;
}

ImagenCajaMetal::~ImagenCajaMetal() {}
