#ifndef NIVEL_H_
#define NIVEL_H_

#include "Escenario.h"

class Nivel {
public:
	Nivel(Escenario* escenario);
	virtual ~Nivel();

	virtual void tick(int milisegundos) = 0;
	virtual bool finalizoPartida() = 0;
	virtual void cargarXML(std::string path);

	Escenario* getEscenario() { return this->escenario; }

protected:
	Escenario* escenario;
};

#endif
