// Header Include.
#include "EscenarioObservable.h"

EscenarioObservable::EscenarioObservable() {
	this->observador = 0;
}

EscenarioObservable::~EscenarioObservable() { }

void EscenarioObservable::registrarObservador(ObservadorEscenario* observador) {
	this->observador = observador;
}

void EscenarioObservable::eliminarObservador() {
	this->observador = 0;
}
