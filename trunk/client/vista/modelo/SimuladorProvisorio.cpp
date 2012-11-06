#include "SimuladorProvisorio.h"
#include <iostream>

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
		std::cout << std::endl;
		usleep(20000);
	}
	return NULL;
}
