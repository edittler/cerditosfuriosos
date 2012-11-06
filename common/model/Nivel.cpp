#include "Nivel.h"

Nivel::Nivel() {
	// TODO carga del escenario y las probabilidades para el simulador
	simulador = new Simulador(20, 50, 10);
}

Nivel::~Nivel() {
	delete escenario;
	delete simulador;
}

