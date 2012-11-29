// Header Include.
#include "Partida.h"

#include "Escenario.h"
#include "../modelo/NivelServer.h"

Partida::Partida(unsigned int id, std::string nombre) {
	this->id = id;
	this->nombre = nombre;
	this->estado = CREANDO;
	this->nivel = new NivelServer();
	this->contadorNiveles = 0;
}

Partida::~Partida() { }

bool Partida::comienzo() {
	return this->nivel->comienzoPartida();
}

bool Partida::finalizo() {
	return (this->estado == FINALIZADO);
}

void Partida::setRutaMundo(std::string path) {
	this->rutaMundo = path;
}

void Partida::cargarSiguienteNivel() {
	++this->contadorNiveles;
	this->nivel->cargarXML(idNiveles[contadorNiveles]);
}

std::string Partida::getXMLNivel() {
	XMLDocument doc;
	bool cargoArchivo = doc.LoadFile(idNiveles[contadorNiveles]);
	if (cargoArchivo == false) {
		std::cout << "\tError al abrir el archivo XML." << std::endl;
		return std::string();
	}
	TiXmlPrinter printer;
	printer.SetIndent("");
	printer.SetLineBreak("");
	doc.Accept(&printer);
	return printer.CStr();
}

unsigned int Partida::getIdJugadorNoConectado() {
	return this->nivel->getEscenario()->getIdJugadorNoConectado();
}

void Partida::setIdJugadorConectado(unsigned int id) {
	this->nivel->getEscenario()->setJugadorConectado(id);
}

void Partida::setIdJugadorNoConectado(unsigned int id) {
	this->nivel->getEscenario()->setJugadorNoConectado(id);
}

EstadoPartida Partida::getEstado() {
	return this->estado;
}

void Partida::setEstado(EstadoPartida estado) {
	this->estado = estado;
}

unsigned int Partida::getId() {
	return this->id;
}

unsigned int Partida::proximoId = 0;

unsigned int Partida::generarId() {
	++Partida::proximoId;
	return Partida::proximoId;
}

std::string Partida::getNombre() const {
	return this->nombre;
}

NivelServer* Partida::getNivel() const {
	return this->nivel;
}

bool Partida::hayEventos() {
	return this->getNivel()->hayEventos();
}

Evento Partida::obtenerEvento() {
	return this->getNivel()->obtenerEvento();
}

void Partida::cargarNiveles() {
	XMLDocument doc;
	// abro XML correspondiente al mundo
	bool cargoArchivo = doc.LoadFile(this->rutaMundo);
	// Si no se cargo, lanzo error.
	if (cargoArchivo == false) {
		std::cout << "\tError al abrir el archivo XML." << std::endl;
		return;
	}

	// obtengo nodos 'Niveles'
	const XMLNode* nodo = doc.RootElement();
	nodo = nodo->FirstChildElement("Niveles");

	// Inicializo el contador de niveles
	int i = 1;
	// Cargo el primer nodo de nivel
	const XMLNode* nodoNivel = nodo->FirstChildElement("Nivel");
	// Mientras el nodo de nivel no es nulo, cargo los niveles.
	while (nodoNivel != 0) {
		// Obtengo el nodo con la ruta de archivo del nivel.
		const XMLNode* nodoRuta = nodoNivel->FirstChildElement("Ruta");
		// Si el nodo ruta no es nulo, cargo el nivel en la tabla
		if (nodoRuta != 0) {
			this->idNiveles[i] = nodoRuta->GetText();
			i++;  // Incremento el contador de niveles cargados
		}
		nodoNivel = nodoNivel->NextSiblingElement("Nivel");
	}
}
