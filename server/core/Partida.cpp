// Header Include.
#include "Partida.h"

#include "Escenario.h"
#include "../modelo/NivelServer.h"

Partida::Partida(unsigned int id, std::string nombre) {
	this->id = id;
	this->nombre = nombre;
	this->estado = CREANDO;
	this->nivel = new NivelServer(new Escenario(1));  // FIXME el Escenario deberia levantarse de XML
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
	// TODO al pasarse directamente el id manejado dentro de MensajeCliente
	// tal vez sea necesario realizar algun parseo para averiguar al path local del xml.
	// Ejemplo: id = "mundosDificiles_mundo4" se parsearia a "../../common/mundosDificiles/mundo4"
	this->rutaMundo = path;
}

void Partida::cargarSiguienteNivel() {
	// TODO implementacion provisoria
	// Segun el contador de niveles se deberia cargar el xml adecuado.
	this->nivel->cargarXML("../common/MiMundo-level1.xml");
	++this->contadorNiveles;
}

unsigned int Partida::getIdJugadorNoConectado() {
	return this->nivel->getEscenario()->getIdJugadorNoConectado();
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
