#include "imagen_posicionable.h"

ImagenPosicionable::ImagenPosicionable(const char* ruta, int x, int y):
	Gtk::Image(ruta)
{
	this->x = x;
	this->y = y;	
}

ImagenPosicionable::~ImagenPosicionable() {}
