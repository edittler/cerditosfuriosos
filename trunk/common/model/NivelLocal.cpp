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

bool NivelLocal::finalizoPartida() {
	return escenario->finalizoPartida();
}

void NivelLocal::generarPajaro() {
	int tipoPajaro = simulador->generarPajaro();

	// TODO LOS VALORES DEBEN SER LOS DEL XML
	if (tipoPajaro != NO_PAJARO) {
		int altura = simulador->generarAlturaPajaro(0, 6);

		switch (tipoPajaro) {
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

void NivelLocal::lanzarHuevo(Punto2D posInicial, Velocidad2D velInicial, Jugador* jugador) {
	// TODO Reemplazar la llamada a Escenario->lanzarHuevo por esto
	/*int tipoHuevo = simulador->generarHuevo();

	// TODO LOS VALORES DEBEN SER LOS DEL XML
	if (tipoHuevo != NO_PAJARO) {
		switch (tipoHuevo) {
			case HUEVO_BLANCO:
				escenario->lanzarHuevoBlanco(posInicial, velInicial, jugador);
				break;
			case HUEVO_CODORNIZ:
				escenario->lanzarHuevosCodorniz(posInicial, velInicial, jugador);
				break;
			case HUEVO_POCHE:
				escenario->lanzarHuevoPoche(posInicial, velInicial, jugador);
				break;
			case HUEVO_RELOJ:
				escenario->lanzarHuevoReloj(posInicial, velInicial, jugador);
				break;
		}
	}*/
}