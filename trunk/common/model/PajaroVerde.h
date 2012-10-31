#ifndef PAJAROVERDE_H_
#define PAJAROVERDE_H_

// Hierarchy Include.
#include "Pajaro.h"

class PajaroVerde: public Pajaro {
public:
	PajaroVerde(b2Body* body);
	virtual ~PajaroVerde();
};

#endif /* PAJAROVERDE_H_ */
