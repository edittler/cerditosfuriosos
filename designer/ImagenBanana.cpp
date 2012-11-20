// Header Include.
#include "ImagenBanana.h"

ImagenBanana::ImagenBanana(int x, int y) : ImagenFruta(RUTA_BANANA) {
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

ImagenBanana::~ImagenBanana() { }

XMLNode* ImagenBanana::serialize(const int altoEscenario) const {
	// Serializo la posicion de la imagen
	XMLNode* punto = this->serializarCoordenadas(altoEscenario);
	// Creo el nodo para la imagen
	XMLNode* nodo = new XMLNode("Banana");
	// Agrego el nodo del Punto2D
	nodo->LinkEndChild(punto);
	return nodo;
}
