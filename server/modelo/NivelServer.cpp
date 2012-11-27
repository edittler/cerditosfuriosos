// Header Include.
#include "NivelServer.h"
#include "ConstantesServer.h"

// C++ Library Project
#include <unistd.h>

NivelServer::NivelServer() {
	this->tiempoGeneracionMinimo = 250;
	this->tiempoAcumulado = 0;
	escenario = new Escenario();
	simulador = new Simulador(20, 50, 10);
}

NivelServer::~NivelServer() {
	delete escenario;
}

void NivelServer::tick(int milisegundos) {
	tiempoAcumulado += milisegundos;

	if (tiempoAcumulado >= tiempoGeneracionMinimo) {
		tiempoAcumulado -= tiempoGeneracionMinimo;
		this->generarPajaro();
	}

	escenario->correrTick();

	// TODO validar si hay que enviar E_FIN_NIVEL
	// FIXME manejar sleep igual que en NivelLocal????
	usleep(SERVER_DELTA_LOOP);
}

void NivelServer::lanzarHuevo(TipoDisparo tDisparo, Punto2D posInicial,
		Velocidad2D velInicial, unsigned int idJugador) {
	switch (tDisparo) {
	case T_HUEVO_BLANCO:
		escenario->lanzarHuevoBlanco(posInicial, velInicial, idJugador);
		break;
	case T_HUEVO_CODORNIZ:
		escenario->lanzarHuevosCodorniz(posInicial, velInicial, idJugador);
		break;
	case T_HUEVO_POCHE:
		escenario->lanzarHuevoPoche(posInicial, velInicial, idJugador);
		break;
	case T_HUEVO_RELOJ:
		escenario->lanzarHuevoReloj(posInicial, velInicial, idJugador);
		break;
	default:
		// No realizo nada.
		break;
	}
}

void NivelServer::lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j) {
	// TODO implementar
}

bool NivelServer::comienzoPartida() {
	return this->escenario->jugadoresCompletos();
}

bool NivelServer::finalizoPartida() const {
	return this->escenario->finalizoPartida();
}

void NivelServer::generarPajaro() {
	int tipoPajaro = simulador->generarPajaro();

	if (tipoPajaro != NO_PAJARO) {
		// define velocidad y posicion de lanzado.
		// TODO El rango de lanzamiento debe ser cargada desde el XML.
		float posX = simulador->randomFloat(escenario->getAncho(),
				escenario->getAncho());
		float posY = simulador->randomFloat(escenario->getAlto() / 2,
				escenario->getAlto());

		// TODO la velocidad no es cargada del XML pero debe setearse una velocidad
		// maxima y una direccion predeterminada (en caso de estar contra los bordes).
		int direccion = -1;
		float velX = direccion * simulador->randomFloat(5.0f, 15.0f);
		float velY = simulador->randomFloat(0.0f, 5.0f);

		switch (tipoPajaro) {
		case PAJARO_AZUL: {
			Evento e(T_PAJARO_AZUL, Punto2D(posX, posY), Velocidad2D(velX, velY));
			this->colaMensajes.encolar(e);
			escenario->lanzarPajaroAzul(Punto2D(posX, posY), Velocidad2D(velX, velY));
			break; }
		case PAJARO_ROJO: {
			Evento e(T_PAJARO_ROJO, Punto2D(posX, posY), Velocidad2D(velX, velY));
			this->colaMensajes.encolar(e);
			escenario->lanzarPajaroRojo(Punto2D(posX, posY), Velocidad2D(velX, velY));
			break; }
		case PAJARO_VERDE: {
			Evento e(T_PAJARO_VERDE, Punto2D(posX, posY), Velocidad2D(velX, velY));
			this->colaMensajes.encolar(e);
			escenario->lanzarPajaroVerde(Punto2D(posX, posY), Velocidad2D(velX, velY));
			break; }
		}
	}
}

bool NivelServer::hayEventos() {
	return !this->colaMensajes.estaVacia();
}

Evento NivelServer::obtenerEvento() {
	return this->colaMensajes.obtenerFrente();
}
