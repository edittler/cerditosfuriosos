// Header Include.
#include "Jugador.h"

Jugador::Jugador(Cerdito* cerdito, unsigned int id) {
	this->id = id;
	this->cerdito = cerdito;
	this->conectado = false;
}

Jugador::~Jugador() {
	delete this->cerdito;
}

void Jugador::sumarPuntos(int puntos) {
	this->puntaje.sumarPuntos(puntos);
}

bool Jugador::perdio() {
	return !cerdito->estaVivo();
}

Cerdito* Jugador::getCerdito() {
	return this->cerdito;
}

unsigned int Jugador::getId() const {
	return this->id;
}

bool Jugador::estaConectado() {
	return this->conectado;
}

void Jugador::setConectado(bool conectado) {
	this->conectado = conectado;
}
