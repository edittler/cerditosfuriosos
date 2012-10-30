#ifndef FRUTA_H_
#define FRUTA_H_

// Hierarchy Include.
#include "CuerpoAbstracto.h"

class Fruta: public CuerpoAbstracto {
public:
	Fruta();
	virtual ~Fruta();

	int getPuntosAdquisicion() const;

protected:
	int puntosAdquisicion;
};

#endif /* FRUTA_H_ */
