#ifndef BANANA_H_
#define BANANA_H_

// Hierarchy Include.
#include "Fruta.h"

class Banana: public Fruta {
public:
	Banana(b2Body* body);
	virtual ~Banana();
};

#endif /* BANANA_H_ */
