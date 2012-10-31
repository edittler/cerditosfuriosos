#ifndef PAJAROAZUL_H_
#define PAJAROAZUL_H_

// Hierarchy Include.
#include "Pajaro.h"

class PajaroAzul: public Pajaro {
public:
	PajaroAzul(b2Body* body);
	virtual ~PajaroAzul();
};

#endif /* PAJAROAZUL_H_ */
