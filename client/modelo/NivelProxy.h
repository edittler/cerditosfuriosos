#ifndef NIVELPROXY_H_
#define NIVELPROXY_H_

// Hierarchy Include.
#include "Nivel.h"

// Common Project Includes.
#include "../../common/communication/ColaProtegida.h"
#include "../../common/communication/Evento.h"
#include "../../common/communication/Socket.h"
#include "../../common/communication/ThreadEnviar.h"
#include "../../common/model/Simulador.h"

class NivelProxy: public Nivel {
public:
	NivelProxy(unsigned int idJugador, Socket& socket,
			ColaProtegida<Evento>& colaEventos);

	virtual ~NivelProxy();

	void tick(int milisegundos);

	void lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j);

	bool finalizoPartida() const;

	void procesarEvento(Evento evento);

private:
	void lanzarPajaro(TipoPajaro tPajaro, Punto2D posInicial,
			Velocidad2D velInicial);

	void lanzarHuevo(TipoDisparo tDisparo, Punto2D posInicial,
			Velocidad2D velInicial);

	Simulador simulador;

	Socket& socket;

	ThreadEnviar* tEnviar;

	ColaProtegida<Evento>& colaEventos;

	unsigned int idJugador;

	bool finalizo;

	// Numero de ticks que lleva corriendo el nivel. FIXME provisorio
	int _tick;
};

#endif
