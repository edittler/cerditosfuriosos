#include "Nivel.h"

#include "Constantes.h"

Nivel::Nivel() {
	// TODO carga del escenario y las probabilidades para el simulador
	simulador = new Simulador(20, 50, 10);
}

Nivel::~Nivel() {
	delete escenario;
	delete simulador;
}

void Nivel::generarPajaro() {
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
