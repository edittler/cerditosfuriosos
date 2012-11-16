#ifndef NIVELLOCAL_H_
#define NIVELLOCAL_H_

#include "Nivel.h"
#include "Simulador.h"

class NivelLocal: public Nivel {
public:

	/*
	 * @brief Constructor
	 * @param escenario en el cual se correran ticks.
	 * @param tiempo minimo de generacion de pajaros.
	 */
	NivelLocal(Escenario* escenario, int tiempoGeneracionMinimo);
	virtual ~NivelLocal();

	void tick(int milisegundos);
	bool finalizoPartida();

	/*
	 * @brief genera un pajaro segun las probabilidades establecidas,
	 * ubicandolo dentro de la zona de generacion de pajaros y lo lanza
	 * en el escenario con una velocidad aleatoria.
	 */
	void generarPajaro();

private:
	int tiempoGeneracionMinimo;
	int tiempoAcumulado;

	/* Generador de pajaros */
	Simulador* simulador;
};

#endif
