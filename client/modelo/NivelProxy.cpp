// Header Include.
#include "NivelProxy.h"

// C++ Library Includes.
#include <iostream>

// Common Project Includes.
#include "../../common/communication/MensajeCliente.h"

NivelProxy::NivelProxy(unsigned int idJugador) {
	escenario = new Escenario();
	this->idJugador = idJugador;
	this->finalizo = false;
	this->_tick = 0;
}

NivelProxy::~NivelProxy() {
	delete escenario;
}


void NivelProxy::tick(int milisegundos) {
	escenario->correrTick();
}

void NivelProxy::lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j) {
	// TODO, enviar info al server
}

bool NivelProxy::finalizoPartida() const {
	return finalizo;
}

void NivelProxy::procesarEvento(Evento evento) {
	TipoEvento tipo = evento.getTipoEvento();
	switch (tipo) {
	case E_CORRER_TICK:
		this->escenario->correrTick();
		std::cout << "tick " << this->_tick++ << std::endl;
		break;
	case E_LANZAR_PAJARO:
		this->lanzarPajaro(evento.getTipoPajaro(), evento.getPunto(),
				evento.getVelocidad());
		break;
	case E_LANZAR_DISPARO:
		this->lanzarHuevo(evento.getTipoDisparo(), evento.getPunto(),
				evento.getVelocidad());
		break;
	case E_FIN_NIVEL:
		this->finalizo = true;
		break;
	default:
		// No realizo nada.
		break;
	}
}

void NivelProxy::lanzarPajaro(TipoPajaro tPajaro, Punto2D posInicial,
		Velocidad2D velInicial) {
	switch (tPajaro) {
	case T_PAJARO_ROJO:
		this->escenario->lanzarPajaroRojo(posInicial, velInicial);
		break;
	case T_PAJARO_VERDE:
		this->escenario->lanzarPajaroVerde(posInicial, velInicial);
		std::cout << "lanzo pajaro verde" << std::endl;
		break;
	case T_PAJARO_AZUL:
		this->escenario->lanzarPajaroAzul(posInicial, velInicial);
		break;
	default:
		// No realizo nada.
		break;
	}
	std::cout << "Posicion\tx= " << posInicial.x << "\ty = " << posInicial.y << std::endl;
	std::cout << "Velocidad\tx= " << velInicial.x << "\ty = " << velInicial.y << std::endl;
}

void NivelProxy::lanzarHuevo(TipoDisparo tDisparo, Punto2D posInicial,
		Velocidad2D velInicial) {
	// Creo el evento

	// Creo el mensaje del cliente
	MensajeCliente mensaje;
	switch (tDisparo) {
	case T_HUEVO_BLANCO:
		// TODO implementar.
		break;
	case T_HUEVO_CODORNIZ:
		/* TODO implementar.
		 * tener en cuenta que se lanzan de a 3. por cuestiones óptimas de la red
		 * solo se manda uno solo y los otros 2 los genera el escenario.
		 * Las diferencias de velocidades deben ser comunes entre server-cliente.
		 */
		break;
	case T_HUEVO_POCHE:
		// TODO IMPLEMENTAR.
		break;
	case T_HUEVO_RELOJ:
		// TODO implementar
		break;
	default:
		// No realizo nada.
		break;
	}
}
