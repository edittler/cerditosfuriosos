#ifndef NIVELSERVER_H_
#define NIVELSERVER_H_

#include "../../common/model/Nivel.h"

class NivelServer: public Nivel {
public:
	NivelServer();
	virtual ~NivelServer();

	/*
	 * @brief avanza ticks en el modelo.
	 * @param valor del tick a avanzar (en milisegundos)
	 */
	void tick(int milisegundos);

	void lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j);

	bool comienzoPartida();

	/*
	 * @brief valida que el modelo sigue ejecutandose.
	 * @return ture si finalizo partida, false caso contrario.
	 */
	bool finalizoPartida() const;

	// TODO Provisorio
	void lanzarPajaroVerde(Punto2D punto, Velocidad2D velocidad);
};

#endif /* NIVELSERVER_H_ */
