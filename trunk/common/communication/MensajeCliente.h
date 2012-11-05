#ifndef MENSAJECLIENTE_H_
#define MENSAJECLIENTE_H_

#include "Mensaje.h"

class MensajeCliente: public Mensaje {
public:
	MensajeCliente();
	virtual ~MensajeCliente();

	virtual std::string serealizar() const;
	virtual void deserealizar(std::string& mensaje);
};

#endif /* MENSAJECLIENTE_H_ */
