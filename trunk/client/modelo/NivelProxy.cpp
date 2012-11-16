#include "NivelProxy.h"

NivelProxy::NivelProxy(Escenario* escenario) : Nivel(escenario) {
	// TODO Auto-generated constructor stub
}

NivelProxy::~NivelProxy() {
	// TODO Auto-generated destructor stub
}


void NivelProxy::tick(int milisegundos) {
	escenario->correrTick();
}

bool NivelProxy::finalizoPartida() {
	return escenario->finalizoPartida();
}
