#include "ImagenCajaMetal.h"

ImagenCajaMetal::ImagenCajaMetal(int x, int y) :
	ImagenPosicionable(RUTA_CAJA_METAL)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_CAJA_METAL;
	this->ancho = ANCHO_CAJA_METAL;
	drag_source_set_icon(Gtk::Image(RUTA_CAJA_METAL).get_pixbuf());
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(RUTA_CAJA_METAL);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	imagenFija = manage(new Gtk::Image(buffer));
	drag_source_set_icon(imagenFija->get_pixbuf());
}

ImagenCajaMetal::~ImagenCajaMetal() {}
