#ifndef CAJAVIDRIO_H_
#define CAJAVIDRIO_H_

// Hierarchy Include.
#include "Superficie.h"

class CajaVidrio: public Superficie {
public:
	CajaVidrio(b2Body* body);
	virtual ~CajaVidrio();
};

#endif /* CAJAVIDRIO_H_ */
