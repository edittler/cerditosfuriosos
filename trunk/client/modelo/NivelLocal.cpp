#include "NivelLocal.h"
#include "Constantes.h"

NivelLocal::NivelLocal() {
    this->tiempoGeneracionMinimo = 250;
    this->tiempoAcumulado = 0;
    escenario = new Escenario();
    simulador = new Simulador(20, 50, 10);
}

NivelLocal::~NivelLocal() {
	delete escenario;
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

void NivelLocal::lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j) {
	int huevo = simulador->generarHuevo();

	switch (huevo) {
	case HUEVO_BLANCO:
		this->escenario->lanzarHuevoBlanco(p, v, j);
		break;
	case HUEVO_CODORNIZ:
		this->escenario->lanzarHuevosCodorniz(p, v, j);
		break;
	case HUEVO_POCHE:
		this->escenario->lanzarHuevoPoche(p, v, j);
		break;
	case HUEVO_RELOJ:
		this->escenario->lanzarHuevoReloj(p, v, j);
		break;
	default:
		this->lanzarHuevo(p, v, j);
		break;
	}
}

bool NivelLocal::finalizoPartida() const {
	return escenario->finalizoPartida();
}

void NivelLocal::generarPajaro() {
	int tipoPajaro = simulador->generarPajaro();

	if (tipoPajaro != NO_PAJARO) {
		// define velocidad y posicion de lanzado.
		// TODO El rango de lanzamiento debe ser cargada desde el XML.
		float posX = simulador->randomFloat(escenario->getAncho(), escenario->getAncho());
		float posY = simulador->randomFloat(escenario->getAlto() / 2, escenario->getAlto());

		// TODO la velocidad no es cargada del XML pero debe setearse una velocidad
		// maxima y una direccion predeterminada (en caso de estar contra los bordes).
		int direccion = -1;
		float velX = direccion * simulador->randomFloat(5.0f, 15.0f);
		float velY = simulador->randomFloat(0.0f, 5.0f);

		switch (tipoPajaro) {
			case PAJARO_AZUL:
				escenario->lanzarPajaroAzul(Punto2D(posX, posY), Velocidad2D(velX, velY));
				break;
			case PAJARO_ROJO:
				escenario->lanzarPajaroRojo(Punto2D(posX, posY), Velocidad2D(velX, velY));
				break;
			case PAJARO_VERDE:
				escenario->lanzarPajaroVerde(Punto2D(posX, posY), Velocidad2D(velX, velY));
				break;
		}
	}
}
