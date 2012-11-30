// Header Include.
#include "ImagenPosicionable.h"

// Designer Project Includes.
#include "CFDTools.h"

int ImagenPosicionable::contadorInstancias = 0;

ImagenPosicionable::ImagenPosicionable(const char* ruta): Gtk::EventBox() {
	if (contadorInstancias == 0)
		id += '0';
	else {
		int auxiliar = contadorInstancias;
		while (auxiliar > 0) {
			id.insert(0, 1, (char)((auxiliar % 10) + '0'));
			auxiliar = auxiliar / 10;
		}
	}
	++contadorInstancias;
	contenedorFondo = manage(new Gtk::Fixed());
	add(*contenedorFondo);
	set_events(Gdk::ALL_EVENTS_MASK);
	std::list<Gtk::TargetEntry> listaObjetivos;
	listaObjetivos.push_back(Gtk::TargetEntry("POSICIONABLE"));
	drag_source_set(listaObjetivos);
	signal_drag_data_get().connect(sigc::mem_fun(*this,
								&ImagenPosicionable::imagen_arrastrada));
}

ImagenPosicionable::~ImagenPosicionable() { }

void ImagenPosicionable::imagen_arrastrada(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	selection_data.set(selection_data.get_target(), 8,
			(const guchar*)id.c_str(), id.length());
}

std::string ImagenPosicionable::getId() const {
	return id;
}

int ImagenPosicionable::getX() const {
	return x;
}

int ImagenPosicionable::getY() const {
	return y;
}

void ImagenPosicionable::setX(const int x) {
	this->x = x;
}
		
void ImagenPosicionable::setY(const int y) {
	this->y = y;
}

void ImagenPosicionable::setFondo(const Glib::RefPtr< Gdk::Pixbuf >& fondo) {
	Gtk::Image* imagenConFondo = manage(new Gtk::Image(fondo));
	std::vector<Widget*> hijos = contenedorFondo->get_children();
	if (hijos.size() == 2) {
		contenedorFondo->remove(*hijos[1]);
		contenedorFondo->remove(*hijos[0]);
	} else {
		if (hijos.size() == 3) {
			contenedorFondo->remove(*hijos[2]);
			contenedorFondo->remove(*hijos[1]);
			contenedorFondo->remove(*hijos[0]);
		}
	}
	contenedorFondo->put(*imagenConFondo, 0, 0);
	contenedorFondo->put(*imagenFija, 0, 0);
	contenedorFondo->show_all();
}

void ImagenPosicionable::setFondoConSuelo(
									const Glib::RefPtr< Gdk::Pixbuf >& fondo,
									const Glib::RefPtr< Gdk::Pixbuf >& suelo,
									int altoSuelo) {
	Gtk::Image* imagenFondo = manage(new Gtk::Image(fondo));
	Gtk::Image* imagenSuelo = manage(new Gtk::Image(suelo));
	std::vector<Widget*> hijos = contenedorFondo->get_children();
	if (hijos.size() == 2) {
		contenedorFondo->remove(*hijos[1]);
		contenedorFondo->remove(*hijos[0]);
	} else {
		if (hijos.size() == 3) {
			contenedorFondo->remove(*hijos[2]);
			contenedorFondo->remove(*hijos[1]);
			contenedorFondo->remove(*hijos[0]);
		}
	}
	contenedorFondo->put(*imagenFondo, 0, 0);
	contenedorFondo->put(*imagenSuelo, 0, alto-altoSuelo);
	contenedorFondo->put(*imagenFija, 0, 0);
	contenedorFondo->show_all();
}


float ImagenPosicionable::getXFlotante() const {
	float posXCentrada = ((float)x) + (((float)ancho) / 2);
	return (posXCentrada/PIXELES_SOBRE_METRO);
}

float ImagenPosicionable::getYFlotante(const int altoEscenario) const {
	float posYCentrada = ((float)y) + (((float)alto) / 2);
	float posYReal = ((float)altoEscenario) - posYCentrada;
	return (posYReal)/PIXELES_SOBRE_METRO;
}

XMLNode* ImagenPosicionable::serializarCoordenadas(
		const int altoEscenario) const {
	XMLNode* nodo = new XMLNode("Punto2D");
	float fX = this->getXFlotante();
	float fY = this->getYFlotante(altoEscenario);
	nodo->SetAttribute("x", cfd::floatToString(fX));
	nodo->SetAttribute("y", cfd::floatToString(fY));
	return nodo;
}
