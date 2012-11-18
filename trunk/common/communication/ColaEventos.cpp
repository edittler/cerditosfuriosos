// Header Include.
#include "ColaEventos.h"

// Project Includes.
#include "../thread/Lock.h"

ColaEventos::ColaEventos() { }

ColaEventos::~ColaEventos() { }

bool ColaEventos::estaVacia() {
	Lock(this->m);
	return this->eventos.empty();
}

size_t ColaEventos::tamanio() {
	Lock(this->m);
	return this->eventos.size();
}

void ColaEventos::encolar(const Evento& evento) {
	Lock(this->m);
	this->eventos.push(evento);
}

Evento ColaEventos::obtenerFrente() {
	Lock(this->m);
	Evento e = this->eventos.front();
	this->eventos.pop();
	return e;
}
