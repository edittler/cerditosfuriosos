#ifndef HUEVORELOJ_H_
#define HUEVORELOJ_H_

// Hierarchy Include.
#include "Disparo.h"

class HuevoReloj: public Disparo {
private:
	float danioCerdito;
public:
	HuevoReloj(b2Body* body);
	virtual ~HuevoReloj();
};

#endif
