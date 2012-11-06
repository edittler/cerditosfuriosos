#include "NivelLocal.h"
#include "Constantes.h"

NivelLocal::NivelLocal() {
	// TODO Auto-generated constructor stub
}

NivelLocal::~NivelLocal() {
	// TODO Auto-generated destructor stub
}


void NivelLocal::tick(int milisegundos) {
	// TODO hacer que la generacion de pajaros sea segun el tiempo seteado
	this->generarPajaro();
	escenario->correrTick();
}

void NivelLocal::generarPajaro() {
	int res = simulador->generarPajaro();

	// TODO setear bien los valores, la posicion debe ser aleatoria
	switch (res) {
		case PAJARO_AZUL:
			escenario->lanzarPajaroAzul(Punto2D(0,50), Velocidad2D(5,-5));
			break;
		case PAJARO_ROJO:
			escenario->lanzarPajaroRojo(Punto2D(0,50), Velocidad2D(5,-5));
			break;
		case PAJARO_VERDE:
			escenario->lanzarPajaroVerde(Punto2D(0,50), Velocidad2D(5,-5));
			break;
	}
}
