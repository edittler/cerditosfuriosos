#include "PanelImagenFondo.h"

PanelImagenFondo::PanelImagenFondo(int ancho, int alto, string ruta) {
	set_size_request(ancho, alto);
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(ruta);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	Gtk::Image* imagenFondo = manage(new Gtk::Image(buffer));
	put(*imagenFondo, 0, 0);
}

PanelImagenFondo::~PanelImagenFondo() {}
