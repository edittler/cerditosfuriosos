#ifndef MONTICULO_H_
#define MONTICULO_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"
#include "../parser/Serializable.h"

class Monticulo: public CuerpoAbstracto {
public:
	Monticulo(b2Body* body);
	virtual ~Monticulo();
};

#endif
