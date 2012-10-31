#ifndef CAJAMETAL_H_
#define CAJAMETAL_H_

// Hierarchy Include.
#include "Superficie.h"

class CajaMetal: public Superficie {
public:
	CajaMetal(b2Body* body);
	virtual ~CajaMetal();
};

#endif /* CAJAMETAL_H_ */
