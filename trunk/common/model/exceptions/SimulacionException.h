#ifndef SIMULACIONEXCEPTION_H_
#define SIMULACIONEXCEPTION_H_

#include <exception>

class SimulacionException: public std::exception {
public:
	SimulacionException(const std::string mensaje) throw() {
		this->msj = "Error en la simulación: ";
		this->msj += mensaje;
	}

	virtual ~SimulacionException() throw() { }

	const char* what() const throw() {
		return this->msj.c_str();
	}

private:
	std::string msj;
};

#endif /* SIMULACIONEXCEPTION_H_ */
