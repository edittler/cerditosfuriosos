#ifndef COLAEVENTOS_H_
#define COLAEVENTOS_H_

// C++ Library Includes.
#include <queue>

// Project Includes.
#include "Evento.h"
#include "../thread/Mutex.h"

class ColaEventos {
public:
	ColaEventos();
	virtual ~ColaEventos();

	bool estaVacia();

	size_t tamanio();

	void encolar(const Evento& evento);

	Evento obtenerFrente();

private:
	// Cola de eventos
	std::queue<Evento> eventos;

	// Mutex
	Mutex m;
};

#endif /* COLAEVENTOS_H_ */
