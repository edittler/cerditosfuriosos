#include "ImagenCajaMadera.h"

ImagenCajaMadera::ImagenCajaMadera(int x, int y) :
	ImagenPosicionable(RUTA_CAJA_MADERA)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_CAJA_MADERA;
	this->ancho = ANCHO_CAJA_MADERA;
}

ImagenCajaMadera::~ImagenCajaMadera() {}
