#include "PanelUnJugador.h"

#include "XMLTypes.h"

PanelUnJugador::PanelUnJugador(int ancho,
								int alto,
								string ruta,
								InterfazSelectora* interfaz):
	PanelImagenFondo(ancho, alto, ruta)
{
	pathFileMundos = "../common/mundos/mundos.xml";
	interfazSelectora = interfaz;
	cargarMundos();
	selectorMundos = new SeleccionadorMultiple(ANCHO_SELECTORES,
												ALTO_SELECTORES,
												mundos);
	conectarBotonesMundo();
	cargarNiveles(selectorMundos->getOpcionSeleccionada());
	selectorNiveles = new SeleccionadorMultiple(ANCHO_SELECTORES,
												ALTO_SELECTORES,
												niveles);
	agregarComponentes();
	// Seniales
//	botonSeleccionar->signal_clicked().connect(sigc::mem_fun(*this,
//								&PanelUnJugador::botonSeleccionarClickeado));
	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
										&PanelUnJugador::botonVolverClickeado));
}

PanelUnJugador::~PanelUnJugador() {
	delete selectorMundos;
	delete selectorNiveles;
	delete botonSeleccionar;
	delete botonVolver;
}

void PanelUnJugador::cargarMundos() {
	XMLDocument doc;
	bool seAbrio = doc.LoadFile(pathFileMundos);
	// Si el archivo no existe, salgo sin cargar mundos
	if (!seAbrio) {
		return;
	}

	// Obtengo el nodo raiz
	XMLNode* root = doc.RootElement();
	// Si es nulo, salgo sin realizar nada
	if (root == 0)
		return;

	// Obtengo el primer nodo del mundo
	const XMLNode* nodoMundo = root->FirstChildElement("Mundo");
	// Mientras el nodo de mundo no es nulo, cargo los mundos.
	while (nodoMundo != 0) {
		// Obtengo el atributo de la cantidad de jugadores
		int cantJugadores = 0;
		const char* aCJ = nodoMundo->Attribute("cantJugadores", &cantJugadores);
		/* Si la cadena de caracteres no es nulo (es decir, existe el atributo)
		 * y la cantidad de jugadores es 1, agrego el mundo en el mapa.
		 */
		if ((aCJ != 0) && (cantJugadores == 1)) {
			// Obtengo el nodo con el nombre del Mundo.
			const XMLNode* nodoNombre = nodoMundo->FirstChildElement("Nombre");
			std::string nombreMundo = nodoNombre->GetText();
			// Obtengo el nodo con la ruta de archivo del mundo.
			const XMLNode* nodoRuta = nodoMundo->FirstChildElement("Ruta");
			// Si los nodos no son nulos, cargo el mundo a la tabla
			if ((nodoNombre != 0) && (nodoRuta != 0)) {
				mundos[nombreMundo] = nodoRuta->GetText();
			}
		}
		// Obtengo el siguiente nodo Mundo
		nodoMundo = nodoMundo->NextSiblingElement("Mundo");
	}
}

void PanelUnJugador::cargarNiveles(string ruta) {
	// Se vacia el mapa de niveles para introducir los de otro mundo.
	vaciarMapaNiveles();
	/* Cargo los niveles del mundo cuya ruta donde están almacenados los niveles
	 * es el recibido por parametro.
	 */
	XMLDocument doc;
	bool seAbrio = doc.LoadFile(ruta);
	// Si el archivo no existe, salgo sin cargar mundos
	if (!seAbrio) {
		return;
	}
	const XMLNode* root = doc.RootElement();
	// Obtengo el nodo de niveles
	const XMLNode* nodoNiveles = root->FirstChildElement("Niveles");
	if (nodoNiveles == 0) {
		return;
	}
	// Inicializo el contador de niveles
	int i = 1;
	// Cargo el primer nodo de nivel
	const XMLNode* nodoNivel = nodoNiveles->FirstChildElement("Nivel");
	// Mientras el nodo de nivel no es nulo, cargo los niveles.
	while (nodoNivel != 0) {
		// Obtengo el nodo con la ruta de archivo del nivel.
		const XMLNode* nodoRuta = nodoNivel->FirstChildElement("Ruta");
		// Si el nodo ruta no es nulo, cargo el nivel en la tabla
		if (nodoRuta != 0) {
			niveles[i] = nodoRuta->GetText();
			i++;  // Incremento el contador de niveles cargados
		}
		nodoNivel = nodoNivel->NextSiblingElement("Nivel");
	}
}

void PanelUnJugador::vaciarMapaNiveles() {
	while (!(niveles.empty()))
		niveles.erase(niveles.begin());
}

void PanelUnJugador::mundoSeleccionadoCambiado() {
	cargarNiveles(selectorMundos->getOpcionSeleccionada());
	selectorNiveles->actualizarBotones(niveles);
	selectorNiveles->show_all();
}

void PanelUnJugador::conectarBotonesMundo() {
	int contador = 0;
	while (contador < selectorMundos->cantidadBotones) {
		selectorMundos->botones[contador]->signal_toggled().connect(
			sigc::mem_fun(*this, &PanelUnJugador::mundoSeleccionadoCambiado));
		++contador;
	}
}

void PanelUnJugador::agregarComponentes() {
	Gtk::Label* etiquetaMundos = manage(new Gtk::Label("Seleccione un mundo"));
	Gtk::Label* etiquetaNiveles = manage(new Gtk::Label("Seleccione un nivel"));
	put(*etiquetaMundos, X_ETIQUETA_MUNDOS, Y_ETIQUETAS);
	put(*etiquetaNiveles, X_ETIQUETA_NIVELES, Y_ETIQUETAS);
	put(*selectorMundos, X_SELECTOR_MUNDOS, Y_SELECTORES);
	put(*selectorNiveles, X_SELECTOR_NIVELES, Y_SELECTORES);
	botonSeleccionar = new Gtk::Button("Seleccionar");
	botonSeleccionar->set_size_request(ANCHO_BOTON_SELECCIONAR, ALTO_BOTON_SELECCIONAR);
	put(*botonSeleccionar, X_BOTON_SELECCIONAR, Y_BOTON_SELECCIONAR);
	botonVolver = new Gtk::Button("Volver al menu principal");
	put(*botonVolver, X_BOTON_VOLVER, Y_BOTON_VOLVER);
}

void PanelUnJugador::botonVolverClickeado() {
	interfazSelectora->volverAMenuPrincipal();
}


void PanelUnJugador::botonSeleccionarClickeado() {

}

std::string PanelUnJugador::getRutaNivelSeleccionado() const {
	return selectorNiveles->getOpcionSeleccionada();
}
