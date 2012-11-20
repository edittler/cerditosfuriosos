// Header Include.
#include "ImagenCerdo.h"

ImagenCerdo::ImagenCerdo(int x, int y) : ImagenPosicionable(RUTA_CERDO) {
	this->x = x;
	this->y = y;
	this->alto = ALTO_CERDO;
	this->ancho = ANCHO_CERDO;
	drag_source_set_icon(Gtk::Image(RUTA_CERDO).get_pixbuf());
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(RUTA_CERDO);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	imagenFija = manage(new Gtk::Image(buffer));
	drag_source_set_icon(imagenFija->get_pixbuf());
}

ImagenCerdo::~ImagenCerdo() { }

XMLNode* ImagenCerdo::serialize(const int altoEscenario) const {
	// Serializo la posicion de la imagen
	XMLNode* punto = this->serializarCoordenadas(altoEscenario);
	// Creo el nodo para la imagen
	XMLNode* nodo = new XMLNode("Cerdito");
	// Agrego el nodo del Punto2D
	nodo->LinkEndChild(punto);
	return nodo;
}
