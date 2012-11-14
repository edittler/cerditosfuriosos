#include "Partida.h"

Partida::Partida(unsigned int id) {
	// TODO Auto-generated constructor stub
	this->id = id;
	this->estado = CREANDO;
}

Partida::~Partida() {
	// TODO Auto-generated destructor stub
}

bool Partida::finalizo() {
	return (this->estado == FINALIZADO);
}

EstadoPartida Partida::getEstado() {
	return this->estado;
}
