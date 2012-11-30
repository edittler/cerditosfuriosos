// Header Include.
#include "PanelNivel.h"

// Designer Project Includes.
#include "ConstantesDiseniador.h"
#include "CFDTools.h"

PanelNivel::PanelNivel(std::string rutaMundo, InformableSeleccion* informable) {
	set_size_request(600, 400);
	this->rutaMundo = rutaMundo;
	this->informable = informable;
	// Una vez seteada la ruta del mundo, cargo sus caracteristicas
	this->cargarCaracteristicasMundo();
	// Cargo el selector
	Gtk::HBox* cajaHorizontalUno = manage(new Gtk::HBox(false, 20));
	selector = new SelectorNiveles(idNiveles);
	cajaHorizontalUno->pack_start(*selector);
	botonEditar = new Gtk::Button("Editar nivel seleccionado");
	Gtk::HButtonBox* cajaAuxiliarUno = manage(new Gtk::HButtonBox());
	cajaAuxiliarUno->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarUno->pack_start(*botonEditar, Gtk::PACK_SHRINK);
	cajaHorizontalUno->pack_start(*cajaAuxiliarUno, Gtk::PACK_SHRINK);
	Gtk::Frame* cuadroEditar = manage(new Gtk::Frame("Edite un nivel existente"));
	cuadroEditar->add(*cajaHorizontalUno);
	// Cargo el creador
	Gtk::HBox* cajaHorizontalDos = manage(new Gtk::HBox(false, 20));
	creador = new CreadorNivel(idNiveles.size()+1, informable);
	cajaHorizontalDos->pack_start(*creador);
	botonCrear = new Gtk::Button("Crear nivel nuevo");
	Gtk::HButtonBox* cajaAuxiliarDos = manage(new Gtk::HButtonBox());
	cajaAuxiliarDos->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarDos->pack_start(*botonCrear, Gtk::PACK_SHRINK);
	cajaHorizontalDos->pack_start(*cajaAuxiliarDos, Gtk::PACK_SHRINK);
	Gtk::Frame* cuadroCrear = manage(new Gtk::Frame("Cree un nuevo nivel"));
	cuadroCrear->add(*cajaHorizontalDos);
	// Inicializacion del boton para volver a la seleccion de mundos
	botonVolver = new Gtk::Button();
	Gtk::Image* imagenVolver = manage(new Gtk::Image(
			Gtk::StockID("gtk-go-back"), Gtk::IconSize(Gtk::ICON_SIZE_BUTTON)));
	botonVolver->set_image(*imagenVolver);
	botonVolver->set_tooltip_text("Volver al panel de mundos");
	Gtk::VButtonBox* cajaAuxiliarTres = manage(new Gtk::VButtonBox());
	cajaAuxiliarTres->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarTres->pack_start(*botonVolver, Gtk::PACK_SHRINK);
	// Cargo en el contenedor
	Gtk::VBox* cajaVertical = manage(new Gtk::VBox(false, 30));
	cajaVertical->pack_start(*cuadroEditar);
	cajaVertical->pack_start(*cuadroCrear);
	cajaVertical->pack_start(*cajaAuxiliarTres);
	add(*cajaVertical);
	// Seniales
	botonCrear->signal_clicked().connect(sigc::mem_fun(*this,
											&PanelNivel::botonCrearClickeado));
	botonEditar->signal_clicked().connect(sigc::mem_fun(*this,
											&PanelNivel::botonEditarClickeado));
	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
											&PanelNivel::volverAPanelMundos));
}

PanelNivel::~PanelNivel() {
	delete selector;
	delete creador;
	delete botonEditar;
	delete botonCrear;
}

void PanelNivel::volverAPanelMundos() {
	informable->volverAPanelMundos();
}

int PanelNivel::getCantidadJugadores() const {
	return cantidadJugadores;
}

void PanelNivel::botonCrearClickeado() {
	if (!(creador->imagenSeleccionada())) {
		informable->imagenNoSeleccionada();
		return;
	}
	/////////////////////////////
	// Creo el archivo del nivel.
	/////////////////////////////
	// Creo el nodo del nivel y seteo el atributo duracion.
	XMLNode* nivelNode = new XMLNode("Nivel");
	nivelNode->SetAttribute("duracion", creador->getDuracion());

	// Creo el nodo del escenario y seteo sus atributos de dimensiones.
	XMLNode* escenarioNode = new XMLNode("Escenario");
	// Convierto los valores flotantes a string.
	std::string sAncho = cfd::floatToString(creador->getAnchoEscenario());
	std::string sAlto = cfd::floatToString(creador->getAltoEscenario());
	// Seteo los atributos del nodo del escenario.
	escenarioNode->SetAttribute("ancho", sAncho);
	escenarioNode->SetAttribute("alto", sAlto);

	// Creo el nodo de la imagen del fondo.
	XMLNode* imageFondoNode = new XMLNode("ImagenFondo");
	XMLText* imageFondoText = new XMLText(creador->getRutaImagenFondo());
	imageFondoNode->LinkEndChild(imageFondoText);

	// Creo el nodo de la imagen del suelo.
	XMLNode* imageSueloNode = new XMLNode("ImagenSuelo");
	// FIXME(eze) Esperar a que Tomás agrege el suelo para serializarlo en el XML.
 	XMLText* imageSueloText = new XMLText("../common/images/background/SueloBosque.png");
 	imageSueloNode->LinkEndChild(imageSueloText);

	// Creo el nodo con la cantidad de jugadores.
	XMLNode* jugadoresNode = new XMLNode("Jugadores");
	// Convierto el numero de jugadores a string.
	std::string sJugadores = cfd::intToString(this->cantidadJugadores);
	XMLText* jugadoresText = new XMLText(sJugadores);
	jugadoresNode->LinkEndChild(jugadoresText);

	// Linkeo los atributos del Escenario
	escenarioNode->LinkEndChild(imageFondoNode);
	escenarioNode->LinkEndChild(imageSueloNode);
	escenarioNode->LinkEndChild(jugadoresNode);

	// Linkeo el nodo de escenario en el nodo del nivel.
	nivelNode->LinkEndChild(escenarioNode);

	// Creo un Documento y guardo el archivo.
	XMLDocument doc;
	XMLDeclaration* decl = new XMLDeclaration("1.0", "UTF-8", "");
	doc.LinkEndChild(decl);
	doc.LinkEndChild(nivelNode);

	// Con el nombre del mundo, genero el nombre del mundo.
	int numNivel = this->idNiveles.size() + 1;
	// Genero la ruta.
	std::string nivelFileName = RUTA_CARPETA_MUNDOS + nombreMundo + "-level";
	// Agrego a la ruta el numero de nivel y la extencion
	std::string sNumNivel = cfd::intToString(numNivel);
	nivelFileName += sNumNivel + ".xml";
	// Guardo el archivo del nivel
	doc.SaveFile(nivelFileName);

	// Actualizo el archivo del mundo.
	this->actualizarArchivoMundo(nivelFileName);

	/* Una vez creado el archivo del nivel y actualizar el del mundo, procedo
	 * a editar el nivel, pasando la ruta del archivo creado y especificando
	 * que el nivel es nuevo, para que seteen algunos valores por defecto.
	 */
	informable->editarNivel(nivelFileName, true);
}

void PanelNivel::botonEditarClickeado() {
	if (idNiveles.size() > 0)
		informable->editarNivel(selector->getRutaNivelSeleccionado(), false);
}

void PanelNivel::cargarCaracteristicasMundo() {
	// Abro el archivo del mundo
	XMLDocument doc;
	bool seCargo = doc.LoadFile(rutaMundo);
	// Si no se cargo, salgo.
	if (!seCargo)
		return;
	// Obtengo el nodo raiz, que debe ser el llamado "Mundo"
	XMLNode* root = doc.RootElement();

	// Obtengo el nodo Nombre y cargo el atributo
	const XMLNode* nodoNombre = root->FirstChildElement("Nombre");
	if (nodoNombre != 0) {
		this->nombreMundo = nodoNombre->GetText();
	}

	// Obtengo el nodo Jugadores y cargo el atributo
	const XMLNode* nodoJugadores = root->FirstChildElement("Jugadores");
	if (nodoJugadores != 0) {
		std::string sJugadores = nodoJugadores->GetText();
		this->cantidadJugadores = cfd::stringToInt(sJugadores);
	}

	// Obtengo el nodo Niveles y cargo los niveles.
	const XMLNode* nodoNiveles = root->FirstChildElement("Niveles");
	if (nodoNiveles != 0)
		this->cargarNiveles(nodoNiveles);
}

void PanelNivel::cargarNiveles(const XMLNode* nodoNiveles) {
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
			idNiveles[i] = nodoRuta->GetText();
			i++;  // Incremento el contador de niveles cargados
		}
		nodoNivel = nodoNivel->NextSiblingElement("Nivel");
	}
}

void PanelNivel::actualizarArchivoMundo(const std::string rutaNivel) const {
	// Abro el archivo del mundo
	XMLDocument doc;
	bool seCargo = doc.LoadFile(rutaMundo);
	// Si no se cargo, salgo.
	if (!seCargo)
		return;
	// Obtengo el nodo raiz, que debe ser el llamado "Mundo"
	XMLNode* root = doc.RootElement();

	// Obtengo el nodo Niveles y cargo el nivel
	XMLNode* nodoNiveles = root->FirstChildElement("Niveles");
	// Si el nodo Niveles es nulo, salgo.
	if (nodoNiveles == 0)
		return;

	// Creo el nodo del ruta
	XMLNode* nodoRuta = new XMLNode("Ruta");
	XMLText* textRuta = new XMLText(rutaNivel);
	nodoRuta->LinkEndChild(textRuta);

	// Creo el nodo del nivel y linkeo la ruta
	XMLNode* nodoNivel = new XMLNode("Nivel");
	nodoNivel->LinkEndChild(nodoRuta);

	// Linkeo el nodo del nivel a Niveles y guardo el documento
	nodoNiveles->LinkEndChild(nodoNivel);
	doc.SaveFile();
}
