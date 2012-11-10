#ifndef NIVEL_H_
#define NIVEL_H_

#include "Escenario.h"

class Nivel {
protected:
	Escenario* escenario;
public:
	Nivel(Escenario* escenario);
	virtual ~Nivel();

	virtual void tick(int milisegundos) = 0;
	virtual bool finalizoPartida() = 0;
};

#endif
