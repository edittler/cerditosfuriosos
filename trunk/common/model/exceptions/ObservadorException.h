#ifndef OBSERVADOREXCEPTION_H_
#define OBSERVADOREXCEPTION_H_

#include <exception>
#include <string>

class ObservadorException: public std::exception {
public:
	ObservadorException(const std::string mensaje) throw() {
		this->msj = "ObservadorException: ";
		this->msj += mensaje;
	}

	virtual ~ObservadorException() throw() { }

	const char* what() const throw() {
		return this->msj.c_str();
	}

private:
	std::string msj;
};

#endif /* OBSERVADOREXCEPTION_H_ */
