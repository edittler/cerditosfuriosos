#ifndef PARSEREXCEPTION_H_
#define PARSEREXCEPTION_H_

#include <exception>

class ParserException: public std::exception {
public:
	ParserException(const std::string mensaje) throw() {
		this->msj = "Error al agregar un objeto: ";
		this->msj += mensaje;
	}

	virtual ~ParserException() throw() { }

	const char* what() const throw() {
		return this->msj.c_str();
	}

private:
	std::string msj;
};

#endif /* PARSEREXCEPTION_H_ */
