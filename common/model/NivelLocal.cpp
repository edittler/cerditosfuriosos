#include "NivelLocal.h"
#include "Constantes.h"

NivelLocal::NivelLocal(Escenario* escenario, int tiempoGeneracionMinimo) : Nivel(escenario) {
    this->tiempoGeneracionMinimo = tiempoGeneracionMinimo;
    this->tiempoAcumulado = 0;
    
    simulador = new Simulador(20, 50, 10);
}

NivelLocal::~NivelLocal() {
    delete simulador;
}

void NivelLocal::tick(int milisegundos) {	
    tiempoAcumulado += milisegundos;
    
    if (tiempoAcumulado >= tiempoGeneracionMinimo) {
        tiempoAcumulado -= tiempoGeneracionMinimo;
        this->generarPajaro();        
    }
    
    escenario->correrTick();
}

void NivelLocal::generarPajaro() {
	int res = simulador->generarPajaro();

	// TODO setear bien los valores, la posicion debe ser aleatoria
	switch (res) {
		case PAJARO_AZUL:
			escenario->lanzarPajaroAzul(Punto2D(13, 6), Velocidad2D(-10, 0));
			break;
		case PAJARO_ROJO:
			escenario->lanzarPajaroRojo(Punto2D(13, 6), Velocidad2D(-10, 0));
			break;
		case PAJARO_VERDE:
			escenario->lanzarPajaroVerde(Punto2D(13, 6), Velocidad2D(-10, 0));
			break;
	}
}
