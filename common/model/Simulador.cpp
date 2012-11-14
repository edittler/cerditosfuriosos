#include "Simulador.h"

#include "cstdlib"
#include "Constantes.h"

Simulador::Simulador(int pAzul, int pRojo, int pVerde) {
	this->probabilidadPajaroAzul = pAzul;
	this->probabilidadPajaroRojo = pRojo;
	this->probabilidadPajaroVerde = pVerde;
}

Simulador::~Simulador() { }

//int Simulador::generarHuevo() {
//	int nroGenerado = rand() % 4;
//
//	if (nroGenerado < HB_PROBABILIDAD) {
//		return HUEVO_BLANCO;
//	} else if (nroGenerado - HB_PROBABILIDAD  < HC_PROBABILIDAD) {
//		return HUEVO_CODORNIZ;
//	} else if (nroGenerado - HB_PROBABILIDAD - HC_PROBABILIDAD < HP_PROBABILIDAD) {
//		return HUEVO_POCHE;
//	}
//
//	return HUEVO_RELOJ;
//}

int Simulador::generarPajaro() {
	int nroGenerado = rand() % 100;

	if (nroGenerado < probabilidadPajaroAzul) {
		return PAJARO_AZUL;
	}else if (nroGenerado - probabilidadPajaroAzul  < probabilidadPajaroRojo) {
		return PAJARO_ROJO;
	}else if (nroGenerado - probabilidadPajaroAzul - probabilidadPajaroRojo <
			  probabilidadPajaroVerde) {
		return PAJARO_VERDE;
	}

	return NO_PAJARO;
}

float Simulador::randomFloat(float min, float max) {
	if (max == min)  // limites iguales.
		return max;
	// Genero random entre limites.
	float nroGenerado = (min + (float) rand() / ((float) RAND_MAX / (max - min)));
	return nroGenerado;
}
