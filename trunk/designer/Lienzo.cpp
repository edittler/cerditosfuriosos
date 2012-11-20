// Header Include.
#include "Lienzo.h"

Lienzo::Lienzo(int ancho,
				int alto,
				int cantidadJugadores,
				string rutaFondo,
				InformableSeleccion* informable) {
	this->cantidadJugadores = cantidadJugadores;
	this->ancho = ancho;
	this->alto = alto;
	this->informable = informable;
	monticulo = NULL;
	agregarFondo(rutaFondo);
	set_size_request(ancho, alto);
	listaObjetivos.push_back(Gtk::TargetEntry("POSICIONABLE"));
	drag_dest_set(listaObjetivos);
	this->signal_drag_data_received().connect(sigc::mem_fun(*this,
		&Lienzo::recibirInformacion));
}

Lienzo::~Lienzo() {}

void Lienzo::eliminarImagen(string id) {
	// Elimino en la lista de posicionables
	eliminarPosicionable(id);

	// Recorro la lista de cerdos para eliminarlo en caso de que lo sea.
	list<ImagenCerdo*>::iterator itCerdo = cerdos.begin();
	while (itCerdo != cerdos.end()) {
		if ((*itCerdo)->getId().compare(id) == 0) {
			remove(*(*itCerdo));
			cerdos.erase(itCerdo);
			return;
		}
		++itCerdo;
	}

	// Recorro la lista de catapultas para eliminarla en caso de que lo sea.
	list<ImagenCatapulta*>::iterator itCatapulta = catapultas.begin();
	while (itCatapulta != catapultas.end()) {
		if ((*itCatapulta)->getId().compare(id) == 0) {
			remove(*(*itCatapulta));
			catapultas.erase(itCatapulta);
			return;
		}
		++itCatapulta;
	}

	// Verifico si es el monticulo para eliminarlo en caso de que lo sea.
	if (monticulo != NULL) {
		if (monticulo->getId().compare(id) == 0) {
			remove(*monticulo);
			monticulo = NULL;
			return;
		}
	}

	// Recorro la lista de superficies para eliminarla en caso de que lo sea.
	list<ImagenSuperficie*>::iterator itSuperficie = superficies.begin();
	while (itSuperficie != superficies.end()) {
		if ((*itSuperficie)->getId().compare(id) == 0) {
			remove(*(*itSuperficie));
			superficies.erase(itSuperficie);
			return;
		}
		++itSuperficie;
	}

	// Recorro la lista de frutas para eliminarla en caso de que lo sea.
	list<ImagenFruta*>::iterator itFruta = frutas.begin();
	while (itFruta != frutas.end()) {
		if ((*itFruta)->getId().compare(id) == 0) {
			remove(*(*itFruta));
			frutas.erase(itFruta);
			return;
		}
		++itFruta;
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
									agregarMonticulo(x, y);
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

void Lienzo::agregarFondo(string rutaImagen) {
	Glib::RefPtr<Gdk::Pixbuf> buffer;
	buffer = Gdk::Pixbuf::create_from_file(rutaImagen);
	buffer = buffer->scale_simple(ancho, alto, Gdk::INTERP_BILINEAR);
	imagenFondo = manage(new Gtk::Image(buffer));
	put(*imagenFondo, 0, 0);
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

void Lienzo::copiarFondo(int x, int y, ImagenPosicionable* imagen) {
	Glib::RefPtr<Gdk::Pixbuf> buffer = imagenFondo->get_pixbuf();
	Glib::RefPtr<Gdk::Pixbuf> fondo = Gdk::Pixbuf::create_subpixbuf(buffer, x, y, imagen->ancho, imagen->alto);
	imagen->setFondo(fondo);
}

void Lienzo::agregarCerdo(int x, int y) {
	if (cerdos.size() < cantidadJugadores) {
		ImagenCerdo* imagen = new ImagenCerdo(x, y);
		if (!coincidenciaOcupacional(x, y, imagen)) {
			if (dentroDeEscenario(x, y, imagen)) {
				copiarFondo(x, y, imagen);
				manage(imagen);
				cerdos.push_back(imagen);
				posicionables.push_back(imagen);
				put(*imagen, x, y);
				show_all();
				return;
			} else
			informable->mostrarDialogo("Fuera de los límites del escenario");
		} else
			informable->mostrarDialogo("Coincide ocupacionalmente con otro objeto");
		delete imagen;
	} else
		informable->mostrarDialogo("Ya ha agregado a todos los jugadores del nivel");
}

void Lienzo::agregarMonticulo(int x, int y) {
	if (monticulo == NULL) {
		ImagenHuevos* imagen = new ImagenHuevos(x, y);
		if (!coincidenciaOcupacional(x, y, imagen)) {
			if (dentroDeEscenario(x, y, imagen)) {
				copiarFondo(x, y, imagen);
				manage(imagen);
				monticulo = imagen;
				posicionables.push_back(imagen);
				put(*imagen, x, y);
				show_all();
				return;
			} else
				informable->mostrarDialogo("Fuera de los límites del escenario");
		} else
			informable->mostrarDialogo("Coincide ocupacionalmente con otro objeto");
		delete imagen;
	} else
		informable->mostrarDialogo("Ya ha agregado un montículo al nivel");
}

void Lienzo::agregarCatapulta(int x, int y) {
	if (catapultas.size() < cantidadJugadores) {
		ImagenCatapulta* imagen = new ImagenCatapulta(x, y);
		if (!coincidenciaOcupacional(x, y, imagen)) {
			if (dentroDeEscenario(x, y, imagen)) {
				copiarFondo(x, y, imagen);
				manage(imagen);
				catapultas.push_back(imagen);
				posicionables.push_back(imagen);
				put(*imagen, x, y);
				show_all();
				return;
			} else
				informable->mostrarDialogo("Fuera de los límites del escenario");
		} else
			informable->mostrarDialogo("Coincide ocupacionalmente con otro objeto");
		delete imagen;
	} else
		informable->mostrarDialogo("Ya ha agregado una catapulta por cada jugador del nivel");
}

void Lienzo::agregarCajaMadera(int x, int y) {
	ImagenCajaMadera* imagen = new ImagenCajaMadera(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			copiarFondo(x, y, imagen);
			manage(imagen);
			superficies.push_back(imagen);
			posicionables.push_back(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		} else
			informable->mostrarDialogo("Fuera de los límites del escenario");
	} else
		informable->mostrarDialogo("Coincide ocupacionalmente con otro objeto");
	delete imagen;
}

void Lienzo::agregarCajaMetal(int x, int y) {
	ImagenCajaMetal* imagen = new ImagenCajaMetal(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			copiarFondo(x, y, imagen);
			manage(imagen);
			superficies.push_back(imagen);
			posicionables.push_back(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		} else
			informable->mostrarDialogo("Fuera de los límites del escenario");
	} else
		informable->mostrarDialogo("Coincide ocupacionalmente con otro objeto");
	delete imagen;
}

void Lienzo::agregarCajaVidrio(int x, int y) {
	ImagenCajaVidrio* imagen = new ImagenCajaVidrio(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			copiarFondo(x, y, imagen);
			manage(imagen);
			superficies.push_back(imagen);
			posicionables.push_back(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		} else
			informable->mostrarDialogo("Fuera de los límites del escenario");
	} else
		informable->mostrarDialogo("Coincide ocupacionalmente con otro objeto");
	delete imagen;
}

void Lienzo::agregarBanana(int x, int y) {
	ImagenBanana* imagen = new ImagenBanana(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			copiarFondo(x, y, imagen);
			manage(imagen);
			frutas.push_back(imagen);
			posicionables.push_back(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		} else
			informable->mostrarDialogo("Fuera de los límites del escenario");
	} else
		informable->mostrarDialogo("Coincide ocupacionalmente con otro objeto");
	delete imagen;
}

void Lienzo::agregarCereza(int x, int y) {
	ImagenCereza* imagen = new ImagenCereza(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			copiarFondo(x, y, imagen);
			manage(imagen);
			frutas.push_back(imagen);
			posicionables.push_back(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		} else
			informable->mostrarDialogo("Fuera de los límites del escenario");
	} else
		informable->mostrarDialogo("Coincide ocupacionalmente con otro objeto");
	delete imagen;
}

void Lienzo::agregarManzana(int x, int y) {
	ImagenManzana* imagen = new ImagenManzana(x, y);
	if (!coincidenciaOcupacional(x, y, imagen)) {
		if (dentroDeEscenario(x, y, imagen)) {
			copiarFondo(x, y, imagen);
			manage(imagen);
			frutas.push_back(imagen);
			posicionables.push_back(imagen);
			put(*imagen, x, y);
			show_all();
			return;
		} else
			informable->mostrarDialogo("Fuera de los límites del escenario");
	} else
		informable->mostrarDialogo("Coincide ocupacionalmente con otro objeto");
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
					copiarFondo(x, y, (*iterador));
					move(*(*iterador), x, y);
				} else
					informable->mostrarDialogo("Fuera de los límites del escenario");
			} else
				informable->mostrarDialogo("Coincide ocupacionalmente con otro objeto");
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
	if (cerdos.size() == catapultas.size()) {
		if (monticulo != NULL)
			return cantidadJugadoresValida();
	}
	return false;
}

void Lienzo::cargarNivel(string rutaNivel) {
	/* 
	 * Informacion para Eze:
	 * 
	 * Este metodo se encargaria de cargar un nivel que ya se empezo a editar.
	 * 
	 * La ruta del mismo es el parametro de este metodo.
	 * 
	 * Sobrecargue los metodos para agregar a todos los objetos para que reciban
	 * los valores flotantes del modelo, los pasen a las coordenadas del
	 * diseñador y se agreguen automaticamente.
	 * 
	 * Entonces habria que ir recorriendo a todos los objetos que se extraigan
	 * del archivo e ir agregandolos mediante los metodos:
	 * 
	 * void agregarCerdo(float x, float y);
	 * void agregarMonticulo(float x, float y);
	 * void agregarCatapulta(float x, float y);
	 * void agregarCajaMadera(float x, float y);
	 * void agregarCajaMetal(float x, float y);
	 * void agregarCajaVidrio(float x, float y);
	 * void agregarBanana(float x, float y);
	 * void agregarCereza(float x, float y);
	 * void agregarManzana(float x, float y);
	 */
}

void Lienzo::guardarNivel(string rutaNivel) {
	// Abro el archivo del nivel
	XMLDocument doc;
	bool fileOpen = doc.LoadFile(rutaNivel);
	if (!fileOpen)
		return;

	// Obtengo el nodo raiz, que en teoría es el llamado Nivel.
	XMLNode* root = doc.RootElement();
	// Obtento el nodo Escenario
	XMLNode* nodoEscenario = root->FirstChildElement("Escenario");
	// Si el nodo no existe, salgo del metodo sin guardar nada
	if (nodoEscenario == 0)
		return;

	/* TODO Este código funciona muy bien cuando se crea un nuevo nivel.
	 * Hay que ver que ocurre en el caso que se edita el nivel, si se borran
	 * los nodos antiguos de cerditos, catapultas, superficies y frutas.
	 * Para ese caso, lo que habría que hacer es respaldar los atributos
	 * y reescribir el archivo XML.
	 */

	// Agrego el nodo del suelo
	XMLNode* nodoSuelo = new XMLNode("Suelo");
	nodoEscenario->LinkEndChild(nodoSuelo);

	/* Serializo los cerdos junto con las catapultas y los agrego al nodo del
	 * escenario.
	 */
	XMLNode* nodoCerdos = this->XMLSerializarCerdos();
	nodoEscenario->LinkEndChild(nodoCerdos);

	// Serializo el montículo de huevos y lo agrego al nodo del escenario.
	XMLNode* nodoMonticulo = this->monticulo->serialize(this->alto);
	nodoEscenario->LinkEndChild(nodoMonticulo);

	// Serializo las superficies y las agrego al nodo del escenario.
	XMLNode* nodoSuperficies = this->XMLSerializarSuperficies();
	nodoEscenario->LinkEndChild(nodoSuperficies);

	// Serializo las frutas y las agrego al nodo del escenario.
	XMLNode* nodoFrutas = this->XMLSerializarFrutas();
	nodoEscenario->LinkEndChild(nodoFrutas);

	// Guardo el documento
	doc.SaveFile();
}

void Lienzo::agregarCerdo(float x, float y) {
	int xEntero = ((int)((x * PIXELES_SOBRE_METRO)-(ANCHO_CERDO / 2)));
	int yEntero = ((int)((((y * PIXELES_SOBRE_METRO)-alto)*-1)-(ALTO_CERDO / 2)));
	agregarCerdo(xEntero, yEntero);
}

void Lienzo::agregarMonticulo(float x, float y) {
	int xEntero = ((int)((x * PIXELES_SOBRE_METRO)-(ANCHO_HUEVOS / 2)));
	int yEntero = ((int)((((y * PIXELES_SOBRE_METRO)-alto)*-1)-(ALTO_HUEVOS / 2)));
	agregarMonticulo(xEntero, yEntero);
}

void Lienzo::agregarCatapulta(float x, float y) {
	int xEntero = ((int)((x * PIXELES_SOBRE_METRO)-(ANCHO_CATAPULTA / 2)));
	int yEntero = ((int)((((y * PIXELES_SOBRE_METRO)-alto)*-1)-(ALTO_CATAPULTA / 2)));
	agregarCatapulta(xEntero, yEntero);
}

void Lienzo::agregarCajaMadera(float x, float y) {
	int xEntero = ((int)((x * PIXELES_SOBRE_METRO)-(ANCHO_CAJA_MADERA / 2)));
	int yEntero = ((int)((((y * PIXELES_SOBRE_METRO)-alto)*-1)-(ALTO_CAJA_MADERA / 2)));
	agregarCajaMadera(xEntero, yEntero);
}

void Lienzo::agregarCajaMetal(float x, float y) {
	int xEntero = ((int)((x * PIXELES_SOBRE_METRO)-(ANCHO_CAJA_METAL / 2)));
	int yEntero = ((int)((((y * PIXELES_SOBRE_METRO)-alto)*-1)-(ALTO_CAJA_METAL / 2)));
	agregarCajaMetal(xEntero, yEntero);
}

void Lienzo::agregarCajaVidrio(float x, float y) {
	int xEntero = ((int)((x * PIXELES_SOBRE_METRO)-(ANCHO_CAJA_VIDRIO / 2)));
	int yEntero = ((int)((((y * PIXELES_SOBRE_METRO)-alto)*-1)-(ALTO_CAJA_VIDRIO / 2)));
	agregarCajaVidrio(xEntero, yEntero);
}

void Lienzo::agregarBanana(float x, float y) {
	int xEntero = ((int)((x * PIXELES_SOBRE_METRO)-(ANCHO_BANANA / 2)));
	int yEntero = ((int)((((y * PIXELES_SOBRE_METRO)-alto)*-1)-(ALTO_BANANA / 2)));
	agregarBanana(xEntero, yEntero);
}

void Lienzo::agregarCereza(float x, float y) {
	int xEntero = ((int)((x * PIXELES_SOBRE_METRO)-(ANCHO_CEREZA / 2)));
	int yEntero = ((int)((((y * PIXELES_SOBRE_METRO)-alto)*-1)-(ALTO_CEREZA / 2)));
	agregarCereza(xEntero, yEntero);
}

void Lienzo::agregarManzana(float x, float y) {
	int xEntero = ((int)((x * PIXELES_SOBRE_METRO)-(ANCHO_MANZANA / 2)));
	int yEntero = ((int)((((y * PIXELES_SOBRE_METRO)-alto)*-1)-(ALTO_MANZANA / 2)));
	agregarManzana(xEntero, yEntero);
}

XMLNode* Lienzo::XMLSerializarCerdos() const {
	// Creo el nodo Cerditos
	XMLNode* nodoCerditos = new XMLNode("Cerditos");
	// Recorro la lista de cerdos y catapultas para ir serializando.
	list<ImagenCerdo*>::const_iterator itCerdo = cerdos.begin();
	list<ImagenCatapulta*>::const_iterator itCatapulta = catapultas.begin();
	while ((itCerdo != cerdos.end()) && (itCatapulta != catapultas.end())) {
		// Serializo el cerdo
		XMLNode* nodoCerdo = (*itCerdo)->serialize(this->alto);
		// Serializo la catapulta y linkeo el nodo en el cerdito
		XMLNode* nodoCatapulta = (*itCatapulta)->serialize(this->alto);
		nodoCerdo->LinkEndChild(nodoCatapulta);
		// Linkeo el cerdo en el nodo de cerdos.
		nodoCerditos->LinkEndChild(nodoCerdo);
		// Incremento los iteradores
		itCerdo++;
		itCatapulta++;
	}
	return nodoCerditos;
}

XMLNode* Lienzo::XMLSerializarSuperficies() const {
	// Creo el nodo Superficies
	XMLNode* nodoSuperficies = new XMLNode("Superficies");
	// Recorro la lista de superficies para ir serializando.
	list<ImagenSuperficie*>::const_iterator itSuperficie = superficies.begin();
	while (itSuperficie != superficies.end()) {
		// Serializo la superficie
		XMLNode* nodoSuperficie = (*itSuperficie)->serialize(this->alto);
		// Linkeo la superficie en el nodo de superficies.
		nodoSuperficies->LinkEndChild(nodoSuperficie);
		// Incremento el iterador.
		itSuperficie++;
	}
	return nodoSuperficies;
}

XMLNode* Lienzo::XMLSerializarFrutas() const {
	// Creo el nodo Superficies
	XMLNode* nodoFrutas = new XMLNode("Frutas");
	// Recorro la lista de frutas para ir serializando.
	list<ImagenFruta*>::const_iterator itFruta = frutas.begin();
	while (itFruta != frutas.end()) {
		// Serializo la fruta
		XMLNode* nodoFruta = (*itFruta)->serialize(this->alto);
		// Linkeo la superficie en el nodo de superficies.
		nodoFrutas->LinkEndChild(nodoFruta);
		// Incremento el iterador.
		itFruta++;
	}
	return nodoFrutas;
}
