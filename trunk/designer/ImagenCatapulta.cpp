#include "ImagenCatapulta.h"

ImagenCatapulta::ImagenCatapulta(int x, int y) :
	ImagenPosicionable(RUTA_CATAPULTA)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_CATAPULTA;
	this->ancho = ANCHO_CATAPULTA;
	drag_source_set_icon(Gtk::Image(RUTA_CATAPULTA).get_pixbuf());
}

ImagenCatapulta::~ImagenCatapulta() {}
