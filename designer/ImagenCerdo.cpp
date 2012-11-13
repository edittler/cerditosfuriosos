#include "ImagenCerdo.h"

ImagenCerdo::ImagenCerdo(int x, int y) :
	ImagenPosicionable(RUTA_CERDO)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_CERDO;
	this->ancho = ANCHO_CERDO;
	drag_source_set_icon(Gtk::Image(RUTA_CERDO).get_pixbuf());
}

ImagenCerdo::~ImagenCerdo() {}
