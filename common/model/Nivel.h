#ifndef NIVEL_H_
#define NIVEL_H_

#include "Escenario.h"

class Nivel {
public:
	Nivel();

	Nivel(Escenario* escenario);

	virtual ~Nivel();

	/*
	 * @brief avanza ticks en el modelo.
	 * @param valor del tick a avanzar (en milisegundos)
	 */
	virtual void tick(int milisegundos) = 0;

	virtual void lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j) = 0;

	/*
	 * @brief valida que el modelo sigue ejecutandose.
	 * @return ture si finalizo partida, false caso contrario.
	 */
	virtual bool finalizoPartida() = 0;

	/*
	 * @brief hidrata el modelo desde un XML.
	 * @param direccion del XML a cargar.
	 */
	virtual void cargarXML(std::string path);

	float getAlto() const;

	Escenario* getEscenario();

protected:
	Escenario* escenario;
};

#endif
