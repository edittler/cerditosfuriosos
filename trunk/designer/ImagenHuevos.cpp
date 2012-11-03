#include "ImagenHuevos.h"

ImagenHuevos::ImagenHuevos(int x, int y) :
	ImagenPosicionable(RUTA_HUEVOS)
{
	this->x = x;
	this->y = y;
}

ImagenHuevos::~ImagenHuevos() {}
