#ifndef VISTACUERPO_H_
#define VISTACUERPO_H_

// Hierarchy Include.
#include "ObservadorCuerpo.h"

class VistaCuerpo: public ObservadorCuerpo {
public:
	VistaCuerpo();
	virtual ~VistaCuerpo();

protected:
	int ajustarValor(float valorFlotante);

private:
//	float round(float f);
};

#endif /* VISTACUERPO_H_ */
