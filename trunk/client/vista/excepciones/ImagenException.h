#ifndef IMAGENEXCEPCION_H_
#define IMAGENEXCEPCION_H_

#include <exception>

class ImagenException: public std::exception {
public:
	ImagenException(const std::string mensaje) throw() {
		this->msj = mensaje;
	}

	virtual ~ImagenException() throw() { }

	const char* what() const throw() {
		return this->msj.c_str();
	}

private:
	std::string msj;
};


#endif /* IMAGENEXCEPCION_H_ */
