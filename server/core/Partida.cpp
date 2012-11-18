// Header Include.
#include "Partida.h"

Partida::Partida(unsigned int id, std::string nombre) {
	this->id = id;
	this->nombre = nombre;
	this->estado = CREANDO;
}

Partida::~Partida() { }

bool Partida::finalizo() {
	return (this->estado == FINALIZADO);
}

EstadoPartida Partida::getEstado() {
	return this->estado;
}
