// Header Include.
#include "NivelServer.h"

NivelServer::NivelServer(Escenario* escenario) : Nivel(escenario) {
	// TODO Auto-generated constructor stub

}

NivelServer::~NivelServer() {
	// TODO Auto-generated destructor stub
}

void NivelServer::tick(int milisegundos) {
	this->escenario->correrTick();
}

bool NivelServer::comienzoPartida() {
	return this->escenario->jugadoresCompletos();
}

bool NivelServer::finalizoPartida() {
	return this->escenario->finalizoPartida();
}

void NivelServer::lanzarPajaroVerde(Punto2D punto, Velocidad2D velocidad) {
	this->escenario->lanzarPajaroVerde(punto, velocidad);
}
