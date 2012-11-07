#ifndef AGREGAROBJETOEXCEPTION_H_
#define AGREGAROBJETOEXCEPTION_H_

#include <exception>

class AgregarObjetoException: public std::exception {
public:
	AgregarObjetoException(const std::string mensaje) throw() {
		this->msj = "Error al agregar un objeto: ";
		this->msj += mensaje;
	}

	virtual ~AgregarObjetoException() throw() { }

	const char* what() const throw() {
		return this->msj.c_str();
	}

private:
	std::string msj;
};

#endif /* AGREGAROBJETOEXCEPTION_H_ */
