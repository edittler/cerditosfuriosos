#include "ImagenBanana.h"

ImagenBanana::ImagenBanana(int x, int y) :
	ImagenPosicionable(RUTA_BANANA)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_BANANA;
	this->ancho = ANCHO_BANANA;
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(RUTA_BANANA);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	imagenFija = manage(new Gtk::Image(buffer));
	drag_source_set_icon(imagenFija->get_pixbuf());
}

ImagenBanana::~ImagenBanana() {}
