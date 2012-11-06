#include "SimuladorProvisorio.h"
#include "ConstantesVistaModelo.h"

#include <iostream> // FIXME eliminar

SimuladorProvisorio::SimuladorProvisorio(Escenario* escenario) {
	this->escenario = escenario;

}

SimuladorProvisorio::~SimuladorProvisorio() {
	// TODO Auto-generated destructor stub
}

void* SimuladorProvisorio::run() {
	/* Hago correr unos ticks.*/
	for (int i=0; i < 500; i++) {
		this->escenario->correrTick();
		std::cout << "tick " << i << std::endl;
		usleep(DELTA_LOOP);
	}
	return NULL;
}
