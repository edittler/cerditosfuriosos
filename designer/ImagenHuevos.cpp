#include "ImagenHuevos.h"

ImagenHuevos::ImagenHuevos(int x, int y) :
	ImagenPosicionable(RUTA_HUEVOS)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_HUEVOS;
	this->ancho = ANCHO_HUEVOS;
	drag_source_set_icon(Gtk::Image(RUTA_HUEVOS).get_pixbuf());
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(RUTA_HUEVOS);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	imagenFija = manage(new Gtk::Image(buffer));
	drag_source_set_icon(imagenFija->get_pixbuf());
}

ImagenHuevos::~ImagenHuevos() {}
