#include "Juego.h"
#include "ConstantesVistaModelo.h"

#include <iostream> // FIXME eliminar
#include "NivelLocal.h"

Juego::Juego(Escenario* escenario) {
        this->nivel = new NivelLocal(escenario, 250);
}

Juego::~Juego() {
	// TODO Auto-generated destructor stub
}

void* Juego::run() {
	int i = 0;
	while (!nivel->finalizoPartida()) {
		this->nivel->tick(20);
		std::cout << "tick " << i++ << std::endl;
		usleep(DELTA_LOOP);
	}

	return NULL;
}
