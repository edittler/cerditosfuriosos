#ifndef NIVELLOCAL_H_
#define NIVELLOCAL_H_

#include "Nivel.h"
#include "Simulador.h"

class NivelLocal: public Nivel {
public:

	/**
	 * Constructor
	 * @param escenario en el cual se correran ticks.
	 * @param tiempo minimo de generacion de pajaros.
	 */
	NivelLocal();

	/**
	 * Destructor
	 */
	virtual ~NivelLocal();

	void tick(int milisegundos);

	void lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j);

	bool finalizoPartida() const;

protected:
	void cargarSimulador(const XMLNode* nodo);

private:
	/*
	 * @brief genera un pajaro segun las probabilidades establecidas,
	 * ubicandolo dentro de la zona de generacion de pajaros y lo lanza
	 * en el escenario con una velocidad aleatoria.
	 */
	void generarPajaro();

	void XMLCargarProbabilidadesPajaros(const XMLNode* nodoPajaros, int& pRojo,
			int& pVerde, int& pAzul);

	int tiempoGeneracionMinimo;
	int tiempoAcumulado;

	/* Generador de pajaros */
	Simulador* simulador;
};

#endif
