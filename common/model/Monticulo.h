#ifndef MONTICULO_H_
#define MONTICULO_H_

#include "CuerpoAbstracto.h"

class Monticulo: public CuerpoAbstracto {
public:
	Monticulo(b2Body* body);
	virtual ~Monticulo();
};

#endif
