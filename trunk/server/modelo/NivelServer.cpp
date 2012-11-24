// Header Include.
#include "NivelServer.h"

NivelServer::NivelServer() {
	escenario = new Escenario();
}

NivelServer::~NivelServer() {
	delete escenario;
}

void NivelServer::tick(int milisegundos) {
	this->escenario->correrTick();
}

void NivelServer::lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j) {
	// TODO implementar
}

bool NivelServer::comienzoPartida() {
	return this->escenario->jugadoresCompletos();
}

bool NivelServer::finalizoPartida() const {
	return this->escenario->finalizoPartida();
}

void NivelServer::lanzarPajaroVerde(Punto2D punto, Velocidad2D velocidad) {
	this->escenario->lanzarPajaroVerde(punto, velocidad);
}
