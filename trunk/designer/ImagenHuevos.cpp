#include "ImagenHuevos.h"

ImagenHuevos::ImagenHuevos(int x, int y) :
	ImagenPosicionable(RUTA_HUEVOS)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_HUEVOS;
	this->ancho = ANCHO_HUEVOS;
	drag_source_set_icon(Gtk::Image(RUTA_HUEVOS).get_pixbuf());
}

ImagenHuevos::~ImagenHuevos() {}
