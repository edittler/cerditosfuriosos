#ifndef NIVEL_H_
#define NIVEL_H_

#include "Escenario.h"
#include "Simulador.h"

class Nivel {
protected:
	Escenario* escenario;
	Simulador* simulador;

	int tiempoGeneracionMinimo;
public:
	Nivel();
	virtual ~Nivel();

	virtual void tick(int milisegundos) = 0;
};

#endif
