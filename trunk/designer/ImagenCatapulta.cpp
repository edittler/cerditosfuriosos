#include "ImagenCatapulta.h"

ImagenCatapulta::ImagenCatapulta(int x, int y) :
	ImagenPosicionable(RUTA_CATAPULTA)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_CATAPULTA;
	this->ancho = ANCHO_CATAPULTA;
	drag_source_set_icon(Gtk::Image(RUTA_CATAPULTA).get_pixbuf());
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(RUTA_CATAPULTA);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	imagenFija = manage(new Gtk::Image(buffer));
	drag_source_set_icon(imagenFija->get_pixbuf());
}

ImagenCatapulta::~ImagenCatapulta() {}
