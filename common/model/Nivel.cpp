#include "Nivel.h"

#include "Constantes.h"

Nivel::Nivel() {
	// TODO carga escenario, valores para el simulador
	simulador = new Simulador(20, 50, 10);
}

Nivel::~Nivel() {
	delete escenario;
	delete simulador;
}

void Nivel::generarPajaro() {
	int res = simulador->generarPajaro();

	switch (res) {
		case PAJARO_AZUL:
			break;
		case PAJARO_ROJO:
			break;
		case PAJARO_VERDE:
			break;
	}
}
