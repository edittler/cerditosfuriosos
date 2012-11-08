#include "SimuladorProvisorio.h"
#include "ConstantesVistaModelo.h"

#include <iostream> // FIXME eliminar
#include "NivelLocal.h"

SimuladorProvisorio::SimuladorProvisorio(Escenario* escenario) {
        this->nivel = new NivelLocal(escenario, 250);
}

SimuladorProvisorio::~SimuladorProvisorio() {
	// TODO Auto-generated destructor stub
}

void* SimuladorProvisorio::run() {
	for(int i = 0; ; i++) {
		this->nivel->tick(20);
		std::cout << "tick " << i << std::endl;
		usleep(DELTA_LOOP);
	}
	return NULL;
}
