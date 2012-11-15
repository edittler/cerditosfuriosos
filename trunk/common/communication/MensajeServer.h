#ifndef MENSAJESERVER_H_
#define MENSAJESERVER_H_

#include "Mensaje.h"

class MensajeServer: public Mensaje {
public:
	MensajeServer();
	virtual ~MensajeServer();

	virtual std::string serealizar() const;
	virtual void deserealizar(const std::string& mensaje);
};

#endif /* MENSAJESERVER_H_ */
