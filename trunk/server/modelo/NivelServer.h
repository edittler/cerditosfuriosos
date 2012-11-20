#ifndef NIVELSERVER_H_
#define NIVELSERVER_H_

#include "../../common/model/Nivel.h"

class NivelServer: public Nivel {
public:
	NivelServer(Escenario* escenario);
	virtual ~NivelServer();

	/*
	 * @brief avanza ticks en el modelo.
	 * @param valor del tick a avanzar (en milisegundos)
	 */
	void tick(int milisegundos);

	bool comienzoPartida();

	/*
	 * @brief valida que el modelo sigue ejecutandose.
	 * @return ture si finalizo partida, false caso contrario.
	 */
	bool finalizoPartida();

	// TODO Provisorio
	void lanzarPajaroVerde(Punto2D punto, Velocidad2D velocidad);
};

#endif /* NIVELSERVER_H_ */
