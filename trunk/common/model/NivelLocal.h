#ifndef NIVELLOCAL_H_
#define NIVELLOCAL_H_

#include "Nivel.h"

class NivelLocal: public Nivel {
public:
	NivelLocal();
	virtual ~NivelLocal();

	void tick(int milisegundos);
	void generarPajaro();
};

#endif
