// Header Include.
#include "CuerpoObservable.h"

CuerpoObservable::CuerpoObservable() {
	// Establezco como NULL el puntero al observador.
	this->observador = 0;
}

CuerpoObservable::~CuerpoObservable() { }

void CuerpoObservable::registrarObservador(ObservadorCuerpo* observador) {
	this->observador = observador;
}

void CuerpoObservable::eliminarObservador() {
	this->observador = 0;
}
