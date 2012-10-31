#ifndef MANZANA_H_
#define MANZANA_H_

// Hierarchy Include.
#include "Fruta.h"

class Manzana: public Fruta {
public:
	Manzana(b2Body* body);
	virtual ~Manzana();
};

#endif /* MANZANA_H_ */
