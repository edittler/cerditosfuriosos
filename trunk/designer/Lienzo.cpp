#include "Lienzo.h"
#include <iostream>
Lienzo::Lienzo(int ancho, int alto) {
	set_size_request(ancho, alto);
	listaObjetivos.push_back(Gtk::TargetEntry("POSICIONABLE"));
	drag_dest_set(listaObjetivos);
	this->signal_drag_data_received().connect(sigc::mem_fun(*this,
		&Lienzo::recibirInformacion));
}

Lienzo::~Lienzo() {}

void Lienzo::eliminarImagen(string id) {
	list<ImagenPosicionable*>::iterator iterador = posicionables.begin();
	while (iterador != posicionables.end()) {
		if ((*iterador)->getId().compare(id) == 0) {
			remove(*(*iterador));
			posicionables.erase(iterador);
			break;
		}
		++iterador;
	}
}

void Lienzo::recibirInformacion(
								const Glib::RefPtr<Gdk::DragContext>& context,
								int x,
								int y,
								const Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	string recepcion = selection_data.get_data_as_string();
	ImagenPosicionable* imagen;
	if (recepcion.compare("CERDO") == 0)
		imagen = new ImagenCerdo(x, y);
	else {
		if (recepcion.compare("HUEVOS") == 0)
			imagen = new ImagenHuevos(x, y);
		else {
			if (recepcion.compare("CAJA_MADERA") == 0)
				imagen = new ImagenCajaMadera(x, y);
			else {
				if (recepcion.compare("CAJA_METAL") == 0)
					imagen = new ImagenCajaMetal(x, y);
				else {
					if (recepcion.compare("CAJA_VIDRIO") == 0)
						imagen = new ImagenCajaVidrio(x, y);
					else {
						moverObjeto(recepcion, x, y);
						return;
					}
				}
			}
		}
	}
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			manage(imagen);
			posicionables.push_front(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		}
	}
	delete imagen;
}

void Lienzo::moverObjeto(string id, int x, int y) {
	list<ImagenPosicionable*>::iterator iterador = posicionables.begin();
	while (iterador != posicionables.end()) {
		if ((*iterador)->getId().compare(id) == 0) {
			if (!coincidenciaOcupacional(x, y, (*iterador))) {
				if (dentroDeEscenario(x, y, (*iterador))) {
					(*iterador)->setX(x);
					(*iterador)->setY(y);
					move(*(*iterador), x, y);
				}
			}
			return;
		}
		++iterador;
	}
}

bool Lienzo::coincidenciaOcupacional(int x, int y, ImagenPosicionable* imagen) {
	bool condicion;
	list<ImagenPosicionable*>::iterator iterador = posicionables.begin();
	while (iterador != posicionables.end()) {
		if (x <= ((*iterador)->getX()+(*iterador)->ancho)&&
			x+imagen->ancho >= ((*iterador)->getX()))
			condicion = (y <= ((*iterador)->getY()+(*iterador)->alto)&&
					y+imagen->alto >= ((*iterador)->getY()));
		if (condicion)
			return true;
		++iterador;
	}
	return false;
}

bool Lienzo::dentroDeEscenario(int x, int y, ImagenPosicionable* imagen) {
	int ancho, alto;
	get_size_request(ancho, alto);
	if (x+imagen->ancho < ancho)
		return (y+imagen->alto < alto);
	return false;
}
