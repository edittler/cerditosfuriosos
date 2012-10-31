#ifndef CEREZA_H_
#define CEREZA_H_

// Hierarchy Include.
#include "Fruta.h"

class Cereza: public Fruta {
public:
	Cereza(b2Body* body);
	virtual ~Cereza();
};

#endif /* CEREZA_H_ */
