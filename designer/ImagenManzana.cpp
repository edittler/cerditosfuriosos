// Header Include.
#include "ImagenManzana.h"

ImagenManzana::ImagenManzana(int x, int y) : ImagenFruta(RUTA_MANZANA) {
	this->x = x;
	this->y = y;
	this->alto = ALTO_MANZANA;
	this->ancho = ANCHO_MANZANA;
	drag_source_set_icon(Gtk::Image(RUTA_MANZANA).get_pixbuf());
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(RUTA_MANZANA);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	imagenFija = manage(new Gtk::Image(buffer));
	drag_source_set_icon(imagenFija->get_pixbuf());
}

ImagenManzana::~ImagenManzana() { }

XMLNode* ImagenManzana::serialize(const int altoEscenario) const {
	// Serializo la posicion de la imagen
	XMLNode* punto = this->serializarCoordenadas(altoEscenario);
	// Creo el nodo para la imagen
	XMLNode* nodo = new XMLNode("Manzana");
	// Agrego el nodo del Punto2D
	nodo->LinkEndChild(punto);
	return nodo;
}
