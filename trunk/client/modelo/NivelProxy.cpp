// Header Include.
#include "NivelProxy.h"

// C++ Library Project
#include <unistd.h>

// Common Project Includes.
#include "MensajeCliente.h"

// Client Project Includes.
#include "../vista/modelo/ConstantesVistaModelo.h"

// Constantes del nivel Proxy
#define MAX_EVENTOS 5

NivelProxy::NivelProxy(unsigned int idJugador, Socket& socket,
		ColaProtegida<Evento>& colaEventos) :
		socket(socket), colaEventos(colaEventos) {
	escenario = new Escenario();
	tEnviar = new ThreadEnviar(socket);
	tEnviar->start();
	this->idJugador = idJugador;
	this->finalizo = false;
	this->_tick = 0;
}

NivelProxy::~NivelProxy() {
	delete escenario;
	delete tEnviar;
}

void NivelProxy::tick(int milisegundos) {
	int i  = 0;
	while ((!colaEventos.estaVacia()) && (i < MAX_EVENTOS)) {
		Evento evento = this->colaEventos.obtenerFrente();
		this->procesarEvento(evento);
	}
}

void NivelProxy::lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j) {
	// Declaro el evento a crear
	Evento evento;
	// Generar mediante el simulador, que tipo de huevo se quiere lanzar
	int huevo = simulador.generarHuevo();
	// Según el tipo de evento que se genero aleatoriamente, seteo el evento.
	switch (huevo) {
	case HUEVO_BLANCO:
		evento.set(T_HUEVO_BLANCO, p, v);
		break;
	case HUEVO_CODORNIZ:
		evento.set(T_HUEVO_CODORNIZ, p, v);
		break;
	case HUEVO_POCHE:
		evento.set(T_HUEVO_POCHE, p, v);
		break;
	case HUEVO_RELOJ:
		evento.set(T_HUEVO_RELOJ, p, v);
		break;
	default:
		evento.set(T_HUEVO_BLANCO, p, v);
		break;
	}
	evento.set(E_PEDIDO_LANZAR_DISPARO);
	// Creo el mensaje del cliente
	Mensaje* mensaje = new MensajeCliente(evento);
	// Agrego al thread que envía mensajes
	tEnviar->agregarMensaje(mensaje);
}

bool NivelProxy::finalizoPartida() const {
	return finalizo;
}

void NivelProxy::procesarEvento(Evento evento) {
	TipoEvento tipo = evento.getTipoEvento();
	switch (tipo) {
	case E_CORRER_TICK:
		this->escenario->correrTick();
		usleep(DELTA_LOOP);
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
		this->tEnviar->finalizar();
		this->tEnviar->join();
		break;
	default:
		// No realizo nada.
		break;
	}
}

void NivelProxy::cargarSimulador(const XMLNode* nodo) { }

void NivelProxy::lanzarPajaro(TipoPajaro tPajaro, Punto2D posInicial,
		Velocidad2D velInicial) {
	switch (tPajaro) {
	case T_PAJARO_ROJO:
		this->escenario->lanzarPajaroRojo(posInicial, velInicial);
		break;
	case T_PAJARO_VERDE:
		this->escenario->lanzarPajaroVerde(posInicial, velInicial);
		break;
	case T_PAJARO_AZUL:
		this->escenario->lanzarPajaroAzul(posInicial, velInicial);
		break;
	default:
		// No realizo nada.
		break;
	}
}

void NivelProxy::lanzarHuevo(TipoDisparo tDisparo, Punto2D posInicial,
		Velocidad2D velInicial) {
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
