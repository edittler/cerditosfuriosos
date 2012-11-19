#ifndef COLAPROTEGIDA_H_
#define COLAPROTEGIDA_H_

// C++ Library Includes.
#include <queue>

// Project Includes.
#include "Evento.h"
#include "../thread/Mutex.h"
#include "../thread/Lock.h"

template <class T> class ColaProtegida {
public:
	ColaProtegida() { }
	virtual ~ColaProtegida() { }

	bool estaVacia() {
		Lock(this->m);
		return this->cola.empty();
	}

	size_t tamanio() {
		Lock(this->m);
		return this->cola.size();
	}

	void encolar(const T evento) {
		Lock(this->m);
		this->cola.push(evento);
	}

	T obtenerFrente() {
		Lock(this->m);
		T e = this->cola.front();
		this->cola.pop();
		return e;
	}

private:
	// Cola de eventos
	std::queue<T> cola;

	// Mutex
	Mutex m;
};

#endif /* COLAPROTEGIDA_H_ */
