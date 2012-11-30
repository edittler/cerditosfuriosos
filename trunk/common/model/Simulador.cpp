#include "Simulador.h"

#include <cstdlib>

#include "XMLTypes.h"
#include "Constantes.h"

#define P_GENERACION_PAJARO		80
#define P_PAJARO_ROJO_DEFAULT	50
#define P_PAJARO_VERDE_DEFAULT	30
#define P_PAJARO_AZUL_DEFAULT	20

Simulador::Simulador() {
	this->probabilidadGeneracion = P_GENERACION_PAJARO;
	this->probabilidadPajaroRojo = P_PAJARO_ROJO_DEFAULT;
	this->probabilidadPajaroVerde = P_PAJARO_VERDE_DEFAULT;
	this->probabilidadPajaroAzul = P_PAJARO_AZUL_DEFAULT;
	this->posX = 0;
	this->posYminima = 0;
	this->posYmaxima = 0;
}

Simulador::Simulador(int probGeneracion, int pRojo, int pVerde, int pAzul,
		float posX, float posYMinima, float posYMaxima) {
	// Si la probabilidad de generacion es negativo, cargo el valor por default
	if (probGeneracion <= 0) {
		this->probabilidadGeneracion = P_GENERACION_PAJARO;
	} else {
		this->probabilidadGeneracion = probGeneracion;
	}
	/* Si las probabilidades de pájaros suma 100, los cargo.
	 * Caso contrario, cargo los valores por default.
	 */
	if ((pRojo + pVerde + pAzul) == 100) {
		this->probabilidadPajaroAzul = pAzul;
		this->probabilidadPajaroRojo = pRojo;
		this->probabilidadPajaroVerde = pVerde;
	} else {
		this->probabilidadPajaroRojo = P_PAJARO_ROJO_DEFAULT;
		this->probabilidadPajaroVerde = P_PAJARO_VERDE_DEFAULT;
		this->probabilidadPajaroAzul = P_PAJARO_AZUL_DEFAULT;
	}
	this->posX = posX;
	this->posYminima = posYMinima;
	this->posYmaxima = posYMaxima;
}

Simulador::~Simulador() { }

int Simulador::generarHuevo() {
	int random = rand() % 100;

	if (random < HB_PROBABILIDAD) {
		return HUEVO_BLANCO;
	} else if (random - HB_PROBABILIDAD  < HC_PROBABILIDAD) {
		return HUEVO_CODORNIZ;
	} else if (random - HB_PROBABILIDAD - HC_PROBABILIDAD < HP_PROBABILIDAD) {
		return HUEVO_POCHE;
	} else if (random - HB_PROBABILIDAD - HC_PROBABILIDAD - HP_PROBABILIDAD
			< HR_PROBABILIDAD) {
		return HUEVO_RELOJ;
	}

	return HUEVO_BLANCO;
}

int Simulador::generarPajaro(Punto2D& punto, Velocidad2D& velocidad) {
	int pajaroGenerado = NO_PAJARO;
	int nroGenerado = rand() % 100;
	if (nroGenerado < this->probabilidadGeneracion) {
		punto = this->generarPosicion();
		velocidad = this->generarVelocidad();
		nroGenerado = rand() % 100;
		if (nroGenerado < probabilidadPajaroAzul) {
			pajaroGenerado = PAJARO_AZUL;
		} else if (nroGenerado - probabilidadPajaroAzul < probabilidadPajaroRojo) {
			pajaroGenerado = PAJARO_ROJO;
		} else if (nroGenerado - probabilidadPajaroAzul - probabilidadPajaroRojo <
				 probabilidadPajaroVerde) {
			pajaroGenerado = PAJARO_VERDE;
		}
		return pajaroGenerado;
	} else {
		return pajaroGenerado;
	}
}

float Simulador::randomFloat(float min, float max) {
	if (max == min)  // limites iguales.
		return max;
	// Genero random entre limites.
	float nroGenerado = (min + (float) rand() / ((float) RAND_MAX / (max - min)));
	return nroGenerado;
}

Punto2D Simulador::generarPosicion() {
	Punto2D p;
	p.x = this->posX;
	p.y = this->randomFloat(this->posYminima, this->posYmaxima);
	return p;
}

Velocidad2D Simulador::generarVelocidad() {
	Velocidad2D v;
	int direccion = -1;
	v.x = direccion * (this->randomFloat(5.0f, 15.0f));
	v.y = this->randomFloat(0.0f, 5.0f);
	return v;
}
