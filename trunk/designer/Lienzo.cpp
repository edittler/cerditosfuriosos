#include "Lienzo.h"

Lienzo::Lienzo(int ancho, int alto, int cantidadJugadores) {
	this->cantidadJugadores = cantidadJugadores;
	this->ancho = ancho;
	this->alto = alto;
	set_size_request(ancho, alto);
	listaObjetivos.push_back(Gtk::TargetEntry("POSICIONABLE"));
	drag_dest_set(listaObjetivos);
	this->signal_drag_data_received().connect(sigc::mem_fun(*this,
		&Lienzo::recibirInformacion));
}

Lienzo::~Lienzo() {}

void Lienzo::eliminarImagen(string id) {
	eliminarPosicionable(id);
	list<ImagenCerdo*>::iterator iterador = cerdos.begin();
	while (iterador != cerdos.end()) {
		if ((*iterador)->getId().compare(id) == 0) {
			remove(*(*iterador));
			cerdos.erase(iterador);
			return;
		}
		++iterador;
	}
	list<ImagenHuevos*>::iterator iteradorDos = huevos.begin();
	while (iteradorDos != huevos.end()) {
		if ((*iteradorDos)->getId().compare(id) == 0) {
			remove(*(*iteradorDos));
			huevos.erase(iteradorDos);
			return;
		}
		++iteradorDos;
	}
	list<ImagenCajaMadera*>::iterator iteradorTres = cajasMadera.begin();
	while (iteradorTres != cajasMadera.end()) {
		if ((*iteradorTres)->getId().compare(id) == 0) {
			remove(*(*iteradorTres));
			cajasMadera.erase(iteradorTres);
			return;
		}
		++iteradorTres;
	}
	list<ImagenCajaMetal*>::iterator iteradorCuatro = cajasMetal.begin();
	while (iteradorCuatro != cajasMetal.end()) {
		if ((*iteradorCuatro)->getId().compare(id) == 0) {
			remove(*(*iteradorCuatro));
			cajasMetal.erase(iteradorCuatro);
			return;
		}
		++iteradorCuatro;
	}
	list<ImagenCajaVidrio*>::iterator iteradorCinco = cajasVidrio.begin();
	while (iteradorCinco != cajasVidrio.end()) {
		if ((*iteradorCinco)->getId().compare(id) == 0) {
			remove(*(*iteradorCinco));
			cajasVidrio.erase(iteradorCinco);
			return;
		}
		++iteradorCinco;
	}
	list<ImagenBanana*>::iterator iteradorSeis = bananas.begin();
	while (iteradorSeis != bananas.end()) {
		if ((*iteradorSeis)->getId().compare(id) == 0) {
			remove(*(*iteradorSeis));
			bananas.erase(iteradorSeis);
			return;
		}
		++iteradorSeis;
	}
	list<ImagenCereza*>::iterator iteradorSiete = cerezas.begin();
	while (iteradorSiete != cerezas.end()) {
		if ((*iteradorSiete)->getId().compare(id) == 0) {
			remove(*(*iteradorSiete));
			cerezas.erase(iteradorSiete);
			return;
		}
		++iteradorSiete;
	}
	list<ImagenManzana*>::iterator iteradorOcho = manzanas.begin();
	while (iteradorOcho != manzanas.end()) {
		if ((*iteradorOcho)->getId().compare(id) == 0) {
			remove(*(*iteradorOcho));
			manzanas.erase(iteradorOcho);
			return;
		}
		++iteradorOcho;
	}
	list<ImagenCatapulta*>::iterator iteradorNueve = catapultas.begin();
	while (iteradorNueve != catapultas.end()) {
		if ((*iteradorNueve)->getId().compare(id) == 0) {
			remove(*(*iteradorNueve));
			catapultas.erase(iteradorNueve);
			return;
		}
		++iteradorNueve;
	}
}

void Lienzo::recibirInformacion(
								const Glib::RefPtr<Gdk::DragContext>& context,
								int x,
								int y,
								const Gtk::SelectionData& selection_data,
								guint info,
								guint time) {
	x = x+2;
	y = y+2;
	string recepcion = selection_data.get_data_as_string();
	if (recepcion.compare("CERDO") == 0)
		agregarCerdo(x, y);
	else {
		if (recepcion.compare("CAJA_MADERA") == 0)
			agregarCajaMadera(x, y);
		else {
			if (recepcion.compare("CAJA_METAL") == 0)
				agregarCajaMetal(x, y);
			else {
				if (recepcion.compare("CAJA_VIDRIO") == 0)
					agregarCajaVidrio(x, y);
				else {
					if (recepcion.compare("BANANA") == 0)
						agregarBanana(x, y);
					else {
						if (recepcion.compare("CEREZA") == 0)
							agregarCereza(x, y);
						else {
							if (recepcion.compare("MANZANA") == 0)
								agregarManzana(x, y);
							else {
								if (recepcion.compare("HUEVOS") == 0)
									agregarHuevos(x, y);
								else {
									if (recepcion.compare("CATAPULTA") == 0)
										agregarCatapulta(x, y);
									else {
										moverObjeto(recepcion, x, y);
										return;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Lienzo::eliminarPosicionable(string id) {
	list<ImagenPosicionable*>::iterator iterador = posicionables.begin();
	while (iterador != posicionables.end()) {
		if ((*iterador)->getId().compare(id) == 0) {
			posicionables.erase(iterador);
			break;
		}
		++iterador;
	}
}

void Lienzo::agregarCerdo(int x, int y) {
	ImagenCerdo* imagen = new ImagenCerdo(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			manage(imagen);
			cerdos.push_front(imagen);
			posicionables.push_front(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		}
	}
	delete imagen;
}

void Lienzo::agregarHuevos(int x, int y) {
	ImagenHuevos* imagen = new ImagenHuevos(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			manage(imagen);
			huevos.push_front(imagen);
			posicionables.push_front(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		}
	}
	delete imagen;
}

void Lienzo::agregarCatapulta(int x, int y) {
	ImagenCatapulta* imagen = new ImagenCatapulta(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			manage(imagen);
			catapultas.push_front(imagen);
			posicionables.push_front(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		}
	}
	delete imagen;
}

void Lienzo::agregarCajaMadera(int x, int y) {
	ImagenCajaMadera* imagen = new ImagenCajaMadera(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			manage(imagen);
			cajasMadera.push_front(imagen);
			posicionables.push_front(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		}
	}
	delete imagen;
}

void Lienzo::agregarCajaMetal(int x, int y) {
	ImagenCajaMetal* imagen = new ImagenCajaMetal(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			manage(imagen);
			cajasMetal.push_front(imagen);
			posicionables.push_front(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		}
	}
	delete imagen;
}

void Lienzo::agregarCajaVidrio(int x, int y) {
	ImagenCajaVidrio* imagen = new ImagenCajaVidrio(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			manage(imagen);
			cajasVidrio.push_front(imagen);
			posicionables.push_front(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		}
	}
	delete imagen;
}

void Lienzo::agregarBanana(int x, int y) {
	ImagenBanana* imagen = new ImagenBanana(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			manage(imagen);
			bananas.push_front(imagen);
			posicionables.push_front(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		}
	}
	delete imagen;
}

void Lienzo::agregarCereza(int x, int y) {
	ImagenCereza* imagen = new ImagenCereza(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			manage(imagen);
			cerezas.push_front(imagen);
			posicionables.push_front(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		}
	}
	delete imagen;
}

void Lienzo::agregarManzana(int x, int y) {
	ImagenManzana* imagen = new ImagenManzana(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			manage(imagen);
			manzanas.push_front(imagen);
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
		if (imagen != *iterador) {
			if (x <= ((*iterador)->getX()+(*iterador)->ancho-1)&&
				(x+imagen->ancho-1) >= ((*iterador)->getX()))
				condicion = (y <= ((*iterador)->getY()+(*iterador)->alto-1)&&
						(y+imagen->alto-1) >= ((*iterador)->getY()));
			if (condicion)
				return true;
		}
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

bool Lienzo::cantidadJugadoresValida() {
	return (cerdos.size() == cantidadJugadores);
}

bool Lienzo::objetosJugadoresCorrectos() {
	if (cerdos.size() == catapultas.size())
		return (cerdos.size() == huevos.size());
	return false;
}
