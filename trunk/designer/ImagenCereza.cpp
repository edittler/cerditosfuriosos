#include "ImagenCereza.h"

ImagenCereza::ImagenCereza(int x, int y) :
	ImagenPosicionable(RUTA_CEREZA)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_CEREZA;
	this->ancho = ANCHO_CEREZA;
	drag_source_set_icon(Gtk::Image(RUTA_CEREZA).get_pixbuf());
}

ImagenCereza::~ImagenCereza() {}
