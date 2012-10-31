#ifndef HUEVOPOCHE_H_
#define HUEVOPOCHE_H_

// Hierarchy Include.
#include "Disparo.h"

class HuevoPoche: public Disparo {
public:
	HuevoPoche(b2Body* body);
	virtual ~HuevoPoche();
};

#endif /* HUEVOPOCHE_H_ */
