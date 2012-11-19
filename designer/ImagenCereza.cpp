// Header Include.
#include "ImagenCereza.h"

ImagenCereza::ImagenCereza(int x, int y) : ImagenFruta(RUTA_CEREZA) {
	this->x = x;
	this->y = y;
	this->alto = ALTO_CEREZA;
	this->ancho = ANCHO_CEREZA;
	drag_source_set_icon(Gtk::Image(RUTA_CEREZA).get_pixbuf());
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(RUTA_CEREZA);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	imagenFija = manage(new Gtk::Image(buffer));
	drag_source_set_icon(imagenFija->get_pixbuf());
}

ImagenCereza::~ImagenCereza() { }
