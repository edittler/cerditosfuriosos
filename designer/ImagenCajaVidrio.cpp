#include "ImagenCajaVidrio.h"

ImagenCajaVidrio::ImagenCajaVidrio(int x, int y) :
	ImagenPosicionable(RUTA_CAJA_VIDRIO)
{
	this->x = x;
	this->y = y;
	this->alto = ALTO_CAJA_VIDRIO;
	this->ancho = ANCHO_CAJA_VIDRIO;
	drag_source_set_icon(Gtk::Image(RUTA_CAJA_VIDRIO).get_pixbuf());
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(RUTA_CAJA_VIDRIO);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	imagenFija = manage(new Gtk::Image(buffer));
	drag_source_set_icon(imagenFija->get_pixbuf());
}

ImagenCajaVidrio::~ImagenCajaVidrio() {}
