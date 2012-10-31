#ifndef SUPERFICIE_H_
#define SUPERFICIE_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

class Superficie: public CuerpoAbstracto {
protected:
	int puntosDestruccion;

public:
	Superficie();
	virtual ~Superficie();

	int getPuntosDestruccion() const;
};

#endif /* SUPERFICIE_H_ */
