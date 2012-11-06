#include "ImagenCajaVidrio.h"

ImagenCajaVidrio::ImagenCajaVidrio(int x, int y) :
	ImagenPosicionable(RUTA_CAJA_VIDRIO)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_CAJA_VIDRIO;
	this->ancho = ANCHO_CAJA_VIDRIO;
}

ImagenCajaVidrio::~ImagenCajaVidrio() {}
