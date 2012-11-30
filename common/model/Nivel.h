#ifndef NIVEL_H_
#define NIVEL_H_

#include "Escenario.h"

class Nivel {
public:
	Nivel();

	virtual ~Nivel();

	/**
	 * Avanza ticks en el modelo.
	 * @param valor del tick a avanzar (en milisegundos)
	 */
	virtual void tick(int milisegundos) = 0;

	virtual void lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j) = 0;

	/**
	 * Valida que el modelo sigue ejecutandose.
	 * @return ture si finalizo partida, false caso contrario.
	 */
	virtual bool finalizoPartida() const = 0;

	/**
	 * Hidrata el modelo desde un XML.
	 * @param direccion del XML a cargar.
	 */
	void cargarXML(std::string path);

	float getAlto() const;

	Escenario* getEscenario();

	Punto2D getPosicionCatapulta(unsigned int idJugador);

protected:
	/**
	 * Carga el simulador, en caso que sea necesario, con las probabilidades
	 * de pájaros.
	 * @param nodo "LineaEntradaDerecha" que contiene las probabilidades.
	 */
	virtual void cargarSimulador(const XMLNode* nodo) = 0;

	Escenario* escenario;
};

#endif
