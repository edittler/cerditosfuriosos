#include "SimuladorProvisorio.h"

SimuladorProvisorio::SimuladorProvisorio(Escenario* escenario) {
	this->escenario = escenario;

}

SimuladorProvisorio::~SimuladorProvisorio() {
	// TODO Auto-generated destructor stub
}

void* SimuladorProvisorio::run() {
	/* Hago correr unos ticks.*/
	for (int i=0; i < 100; i++) {
		this->escenario->correrTick();
	}
	return NULL;
}
