#ifndef NIVELPROXY_H_
#define NIVELPROXY_H_

#include "Nivel.h"

class NivelProxy: public Nivel {
public:
	NivelProxy(Escenario* escenario);
	virtual ~NivelProxy();
};

#endif
