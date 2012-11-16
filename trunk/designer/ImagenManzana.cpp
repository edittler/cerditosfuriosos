#include "ImagenManzana.h"

ImagenManzana::ImagenManzana(int x, int y) :
	ImagenPosicionable(RUTA_MANZANA)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_MANZANA;
	this->ancho = ANCHO_MANZANA;
	drag_source_set_icon(Gtk::Image(RUTA_MANZANA).get_pixbuf());
}

ImagenManzana::~ImagenManzana() {}
