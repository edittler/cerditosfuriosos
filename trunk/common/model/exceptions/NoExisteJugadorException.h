/*
 * NoExisteJugadorException.h
 *
 *  Created on: 28/10/2012
 *      Author: ezequiel
 */

#ifndef NOEXISTEJUGADOREXCEPTION_H_
#define NOEXISTEJUGADOREXCEPTION_H_

#include <exception>

class NoExisteJugadorException: public std::exception {
public:
	NoExisteJugadorException() throw() {
		this->msj = "No existe el jugador de indice especificado.";
	}
	virtual ~NoExisteJugadorException() throw() { }

	const char* what() const throw() {
		return this->msj.c_str();
	}

private:
	std::string msj;
};

#endif /* NOEXISTEJUGADOREXCEPTION_H_ */
