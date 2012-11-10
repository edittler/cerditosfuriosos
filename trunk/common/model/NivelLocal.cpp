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

	if (res != NO_PAJARO) {
		// TODO LOS VALORES DEBEN SER LOS DEL XML
		int altura = simulador->generarAlturaPajaro(0, 6);

		switch (res) {
			case PAJARO_AZUL:
				escenario->lanzarPajaroAzul(Punto2D(10, altura), Velocidad2D(-10, 0));
				break;
			case PAJARO_ROJO:
				escenario->lanzarPajaroRojo(Punto2D(10, altura), Velocidad2D(-10, 0));
				break;
			case PAJARO_VERDE:
				escenario->lanzarPajaroVerde(Punto2D(10, altura), Velocidad2D(-10, 0));
				break;
		}
	}
}
