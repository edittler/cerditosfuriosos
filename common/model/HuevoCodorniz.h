#ifndef HUEVOCODORNIZ_H_
#define HUEVOCODORNIZ_H_

// Hierarchy Include.
#include "Disparo.h"

class HuevoCodorniz: public Disparo {
public:
	HuevoCodorniz(b2Body* body);
	virtual ~HuevoCodorniz();
};

#endif /* HUEVOCODORNIZ_H_ */
