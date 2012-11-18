#include "ImagenCajaMadera.h"

ImagenCajaMadera::ImagenCajaMadera(int x, int y) :
	ImagenPosicionable(RUTA_CAJA_MADERA)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_CAJA_MADERA;
	this->ancho = ANCHO_CAJA_MADERA;
	drag_source_set_icon(Gtk::Image(RUTA_CAJA_MADERA).get_pixbuf());
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(RUTA_CAJA_MADERA);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	imagenFija = manage(new Gtk::Image(buffer));
	drag_source_set_icon(imagenFija->get_pixbuf());
}

ImagenCajaMadera::~ImagenCajaMadera() {}
