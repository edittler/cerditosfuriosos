#include "ImagenCajaVidrio.h"

ImagenCajaVidrio::ImagenCajaVidrio(int x, int y) :
	ImagenPosicionable(RUTA_CAJA_VIDRIO)
{
	this->x = x;
	this->y = y;
}

ImagenCajaVidrio::~ImagenCajaVidrio() {}
