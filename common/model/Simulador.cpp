#include "Simulador.h"

#include "cstdlib"
#include "Constantes.h"

Simulador::Simulador(int pAzul, int pRojo, int pVerde) {
	this->probabilidadPajaroAzul = pAzul;
	this->probabilidadPajaroRojo = pRojo;
	this->probabilidadPajaroVerde = pVerde;
}

Simulador::~Simulador() {
	// TODO Auto-generated destructor stub
}

int Simulador::generarPajaro() {
	int nroGenerado = rand() % 100;

	if (nroGenerado < probabilidadPajaroAzul) {
		return PAJARO_AZUL;
	}else if (nroGenerado + probabilidadPajaroAzul  < probabilidadPajaroRojo) {
		return PAJARO_ROJO;
	}else if (nroGenerado + probabilidadPajaroAzul + probabilidadPajaroRojo <
			  probabilidadPajaroVerde) {
		return PAJARO_VERDE;
	}

	return NO_PAJARO;
}
