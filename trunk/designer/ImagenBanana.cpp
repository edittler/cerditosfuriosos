#include "ImagenBanana.h"

ImagenBanana::ImagenBanana(int x, int y) :
	ImagenPosicionable(RUTA_BANANA)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_BANANA;
	this->ancho = ANCHO_BANANA;
	drag_source_set_icon(Gtk::Image(RUTA_BANANA).get_pixbuf());
}

ImagenBanana::~ImagenBanana() {}
