#include "ImagenCajaMetal.h"

ImagenCajaMetal::ImagenCajaMetal(int x, int y) :
	ImagenPosicionable(RUTA_CAJA_METAL)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_CAJA_METAL;
	this->ancho = ANCHO_CAJA_METAL;
}

ImagenCajaMetal::~ImagenCajaMetal() {}
