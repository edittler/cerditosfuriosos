#ifndef NIVELLOCAL_H_
#define NIVELLOCAL_H_

// Hierarchy Include.
#include "Nivel.h"

// Common Project Includes.
#include "Simulador.h"
#include "Evento.h"
#include "ColaProtegida.h"


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

	/**
	 * Implementación del método virtual puro de la clase Nivel.
	 * Genera un pájaro si se alcanzó el tiempo mínimo de generació, lanza los
	 * disparos que desea el usuario y corre una unidad de tick.
	 * @param milisegundos que se quere correr en la simulación.
	 */
	void tick(int milisegundos);

	void lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j);

	bool finalizoPartida() const;

protected:
	void cargarSimulador(const XMLNode* nodo);

private:
	/**
	 * A partir de un nodo XML que contiene las probabilidades de los pajaros,
	 * decodifica las mismas y las almacena en las referencias especificadas.
	 */
	void XMLCargarProbabilidadesPajaros(const XMLNode* nodoPajaros, int& pRojo,
			int& pVerde, int& pAzul);

	/**
	 * Genera un pajaro segun las probabilidades establecidas, mediante el
	 * simulador y lo agrega al escenario.
	 */
	void generarPajaro();

	/**
	 * Procesa los disparos almacenados en la cola y los lanza en el escenario.
	 */
	void procesarDisparos();

	// Tiempo mínimo que tiene que transcurrir para que se genere un pajaro.
	int tiempoGeneracionMinimo;

	// Tiempo acumulado desde la ultima vez que se generó un pajaro.
	int tiempoAcumulado;

	// Generador de pajaros
	Simulador* simulador;

	// Cola donde se almacenan los disparos solicitados por el usuario
	ColaProtegida<Evento> colaDisparos;
};

#endif
