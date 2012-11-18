#ifndef NIVELPROXY_H_
#define NIVELPROXY_H_

// Hierarchy Include.
#include "Nivel.h"

// Common Project Includes.
#include "../../common/communication/Evento.h"

class NivelProxy: public Nivel {
public:
	NivelProxy(Escenario* escenario);
	virtual ~NivelProxy();

	void tick(int milisegundos);

	bool finalizoPartida();

	void procesarEvento(Evento evento);

private:
	void lanzarPajaro(TipoPajaro tPajaro, Punto2D posInicial,
			Velocidad2D velInicial);

	void lanzarHuevo(TipoDisparo tDisparo, Punto2D posInicial,
			Velocidad2D velInicial);

	bool finalizo;

	// Numero de ticks que lleva corriendo el nivel. FIXME provisorio
	int _tick;
};

#endif
