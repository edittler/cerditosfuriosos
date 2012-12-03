// Header Includes.
#include "PanelEscenario.h"

// Common Project Includes.
#include "XMLTypes.h"

// Designer Project Includes.
#include "CFDTools.h"

PanelEscenario::PanelEscenario(string rutaNivel,
								InformableSeleccion* informable,
								int cantidadJugadores,
								bool nivelNuevo) {
	this->cantidadJugadores = cantidadJugadores;
	this->rutaNivel = rutaNivel;
	this->informable = informable;
	cargarCaracteristicasNivel();
	int ancho = (int)(anchoFlotante * PIXELES_SOBRE_METRO);
	int alto = (int)(altoFlotante * PIXELES_SOBRE_METRO);
	// Inicializacion de los widgets propios
	lienzo = new Lienzo(ancho, alto, cantidadJugadores, rutaFondo, rutaSuelo, informable);
	paletaEscenario = new PaletaEscenario();
	eliminador = new EliminadorPosicionables(lienzo);
	entrada = new EntradaPajaros(anchoFlotante, altoFlotante);
	if (!nivelNuevo) {
		lienzo->cargarNivel(rutaNivel);
		entrada->cargarNivel(rutaNivel);
	}
	// Inicializacion del boton para guardar el nivel
	botonGuardar = new Gtk::Button();
	Gtk::Image* imagenGuardar = manage(new Gtk::Image(
			Gtk::StockID("gtk-floppy"), Gtk::IconSize(Gtk::ICON_SIZE_BUTTON)));
	botonGuardar->set_image(*imagenGuardar);
	Gtk::Label* etiquetaGuardar = manage(new Gtk::Label("Guardar nivel: "));
	// Inicializacion del boton para volver a la seleccion de niveles
	botonVolver = new Gtk::Button();
	Gtk::Image* imagenVolver = manage(new Gtk::Image(
			Gtk::StockID("gtk-go-back"), Gtk::IconSize(Gtk::ICON_SIZE_BUTTON)));
	botonVolver->set_image(*imagenVolver);
	botonVolver->set_tooltip_text("Volver al panel de mundos");
	// Contenedores
	Gtk::VBox* cajaVerticalUno = manage(new Gtk::VBox(false, 20));
	cajaVerticalUno->pack_start(*paletaEscenario);
	cajaVerticalUno->pack_start(*eliminador);
	Gtk::VButtonBox* cajaAuxiliarUno = manage(new Gtk::VButtonBox());
	cajaAuxiliarUno->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarUno->pack_start(*botonGuardar, Gtk::PACK_SHRINK);
	Gtk::VButtonBox* cajaAuxiliarDos = manage(new Gtk::VButtonBox());
	cajaAuxiliarDos->set_layout(Gtk::BUTTONBOX_CENTER);
	cajaAuxiliarDos->pack_start(*botonVolver, Gtk::PACK_SHRINK);
	Gtk::HBox* cajaHorizontalUno = manage(new Gtk::HBox(false, 20));
	cajaHorizontalUno->pack_start(*etiquetaGuardar);
	cajaHorizontalUno->pack_start(*cajaAuxiliarUno);
	Gtk::VBox* cajaVerticalDos = manage(new Gtk::VBox(false, 20));
	cajaVerticalDos->pack_start(*entrada);
	cajaVerticalDos->pack_start(*cajaHorizontalUno, Gtk::PACK_SHRINK);
	cajaVerticalDos->pack_start(*cajaAuxiliarDos, Gtk::PACK_SHRINK);
	Gtk::HBox* cajaHorizontal = manage(new Gtk::HBox(false, 20));
	Gtk::VBox* cajaVerticalLienzo = manage(new Gtk::VBox(false, 0));
	cajaVerticalLienzo->pack_start(*lienzo, Gtk::PACK_SHRINK);
	cajaHorizontal->pack_start(*cajaVerticalUno);
	cajaHorizontal->pack_start(*cajaVerticalLienzo, Gtk::PACK_SHRINK);
	cajaHorizontal->pack_start(*cajaVerticalDos);
	add(*cajaHorizontal);
	// Seniales
	botonGuardar->signal_clicked().connect(sigc::mem_fun(*this,
									&PanelEscenario::botonGuardarClickeado));
	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
										&PanelEscenario::volverAPanelMundos));
}

PanelEscenario::~PanelEscenario() {
	delete paletaEscenario;
	delete lienzo;
	delete eliminador;
	delete entrada;
	delete botonGuardar;
	delete botonVolver;
}

void PanelEscenario::volverAPanelMundos() {
	informable->volverAPanelMundos();
}

bool PanelEscenario::escenarioValido() const {
	bool escenarioValido = true;
	std::string mensaje("Antes de poder guardar debe realizar las siguientes "
			"correciones:\n");
	if (!(entrada->lineaEntradaValida())) {
		escenarioValido = false;
		mensaje += "- La línea de entrada de pajaros no tiene puntos de inicio "
				"y fin válidos\n";
	}
	if (!(entrada->porcentajesPajarosValidos())) {
		escenarioValido = false;
		mensaje += "- Los porcentajes de aparición de los pájaros no suman 100%\n";
	}
	if (!(lienzo->cantidadJugadoresValida())) {
		escenarioValido = false;
		mensaje += "- El numero de jugadores debe ser ";
		mensaje += (char)(cantidadJugadores + '0');
		mensaje += "\n";
	}
	if (!(lienzo->cantidadCatapultasValida())) {
		escenarioValido = false;
		mensaje += "- El numero de catapultas debe ser ";
		mensaje += (char)(cantidadJugadores + '0');
		mensaje += "\n";
	}
	if (!(lienzo->hayMonticulo())) {
		escenarioValido = false;
		mensaje += "- Debe haber un montículo";
	}
	if (!escenarioValido)
		informable->mostrarDialogo(mensaje);
	return escenarioValido;
}

void PanelEscenario::botonGuardarClickeado() {
	if (!escenarioValido())
		return;
	guardarNivel();
}

void PanelEscenario::guardarNivel() {
	/* Reestablezco el archivo del nivel, reescribiendo los atributos del
	 * escenario.
	 */
	this->guardarCaracteristicasEscenario();
	lienzo->guardarNivel(rutaNivel);
	entrada->guardarNivel(rutaNivel);
}

void PanelEscenario::guardarCaracteristicasEscenario() const {
	// Abro el archivo asociado al nivel
	XMLDocument doc;
	doc.LoadFile(this->rutaNivel);
	// Obtengo el nodo raiz, que en teoria es el llamado Nivel.
	XMLNode* nivelNode = doc.RootElement();

	// Limpio el nodo de nivel
	this->limpiarNodoNivel(nivelNode);

	// Creo un nuevo nodo del escenario y cargo los atributos básicos.
	XMLNode* escenarioNode = new XMLNode("Escenario");
	// Convierto los valores flotantes a string.
	std::string sAncho = cfd::floatToString(anchoFlotante);
	std::string sAlto = cfd::floatToString(altoFlotante);
	// Seteo los atributos del nodo del escenario.
	escenarioNode->SetAttribute("ancho", sAncho);
	escenarioNode->SetAttribute("alto", sAlto);

	// Creo el nodo de la imagen del fondo.
	XMLNode* imageFondoNode = new XMLNode("ImagenFondo");
	XMLText* imageFondoText = new XMLText(rutaFondo);
	imageFondoNode->LinkEndChild(imageFondoText);

	// Creo el nodo de la imagen del suelo.
	XMLNode* imageSueloNode = new XMLNode("ImagenSuelo");
	// FIXME(eze) Esperar a que Tomás agrege el suelo para serializarlo en el XML.
	XMLText* imageSueloText = new XMLText(rutaSuelo);
	imageSueloNode->LinkEndChild(imageSueloText);

	// Creo el nodo con la cantidad de jugadores.
	XMLNode* jugadoresNode = new XMLNode("Jugadores");
	// Convierto el numero de jugadores a string.
	std::string sJugadores = cfd::intToString(cantidadJugadores);
	XMLText* jugadoresText = new XMLText(sJugadores);
	jugadoresNode->LinkEndChild(jugadoresText);

	// Linkeo los atributos del Escenario
	escenarioNode->LinkEndChild(imageFondoNode);
	escenarioNode->LinkEndChild(imageSueloNode);
	escenarioNode->LinkEndChild(jugadoresNode);

	// Linkeo el nodo de escenario en el nodo del nivel.
	nivelNode->LinkEndChild(escenarioNode);

	// Guardo el documento.
	doc.SaveFile();
}

void PanelEscenario::cargarCaracteristicasNivel() {
	/* Obtengo desde el archivo XML asociado al nivel, las caracteristicas del
	 * mismo.
	 */
	XMLDocument doc;
	doc.LoadFile(this->rutaNivel);
	const XMLNode* nivelNode = doc.RootElement();

	// Obtengo el nodo del escenario
	const XMLNode* escenarioNode = nivelNode->FirstChildElement("Escenario");

	// Si el nodo es nulo, seteo las dimenciones en tamaño medio y salgo
	if (escenarioNode == 0) {
		anchoFlotante = ANCHO_ESCENARIO_MEDIANO;
		altoFlotante = ALTO_ESCENARIO_MEDIANO;
		return;
	}

	// Obtengo los atributos de dimensiones del escenario.
	std::string sAncho = escenarioNode->Attribute("ancho");
	std::string sAlto = escenarioNode->Attribute("alto");

	// Seteo los atributos de dimensiones
	anchoFlotante = cfd::stringToFloat(sAncho);
	altoFlotante = cfd::stringToFloat(sAlto);

	// Obtengo el nodo de la imagen de fondo
	const XMLNode* imageFondoNode = escenarioNode->
			FirstChildElement("ImagenFondo");
	rutaFondo = imageFondoNode->GetText();

	// Obtengo el nodo de la imagen de suelo
	const XMLNode* imageSueloNode = escenarioNode->
			FirstChildElement("ImagenSuelo");
	rutaSuelo = imageSueloNode->GetText();
}

void PanelEscenario::limpiarNodoNivel(XMLNode* nodo) const {
	// Obtengo el nodo del escenario
	XMLNode* escenarioNode = nodo->FirstChildElement("Escenario");

	/* Mientras el nodo escenario no sea nulo, itero hasta eliminar todos los
	 * nodos llamados "Escenario"
	 */
	while (escenarioNode != 0) {
		XMLNode* nextNode = escenarioNode->NextSiblingElement("Escenario");
		nodo->RemoveChild(escenarioNode);
		escenarioNode = nextNode;
	}

	// Obtengo el nodo de la Linea de entrada derecha
	XMLNode* lineaNode = nodo->FirstChildElement("LineaEntradaDerecha");

	/* Mientras el nodo de linea de entrada no sea nulo, itero hasta eliminar
	 * todos los nodos llamados "LineaEntradaDerecha"
	 */
	while (lineaNode != 0) {
		XMLNode* nextNode = lineaNode->NextSiblingElement("LineaEntradaDerecha");
		nodo->RemoveChild(lineaNode);
		lineaNode = nextNode;
	}
}
