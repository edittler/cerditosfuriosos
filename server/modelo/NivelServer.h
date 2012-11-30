#ifndef NIVELSERVER_H_
#define NIVELSERVER_H_

// Hierarchy Include.
#include "Nivel.h"

// Common Project Includes.
#include "Simulador.h"
#include "Evento.h"
#include "ColaProtegida.h"

class NivelServer: public Nivel {
public:
	NivelServer();
	virtual ~NivelServer();

	/*
	 * @brief avanza ticks en el modelo.
	 * @param valor del tick a avanzar (en milisegundos)
	 */
	void tick(int milisegundos);

	/*
	 * @brief lanza huevo en el escenario
	 * @param informacion necesaria para lanzar disparo.
	 */
	void lanzarHuevo(TipoDisparo tDisparo, Punto2D p, Velocidad2D v,
			unsigned int idJugador);

	void lanzarHuevo(Punto2D p, Velocidad2D v, unsigned int j);

	bool comienzoPartida();

	/*
	 * @brief valida que el modelo sigue ejecutandose.
	 * @return ture si finalizo partida, false caso contrario.
	 */
	bool finalizoPartida() const;

	/*
	 * @brief genera un pajaro segun las probabilidades establecidas,
	 * ubicandolo dentro de la zona de generacion de pajaros y lo lanza
	 * en el escenario con una velocidad aleatoria.
	 */
	void generarPajaro();

	/*
	 * @brief
	 * @return
	 */
	bool hayEventos();

	/*
	 * @brief
	 * @return
	 */
	Evento obtenerEvento();

protected:
	void cargarSimulador(const XMLNode* nodo);

private:
	void XMLCargarProbabilidadesPajaros(const XMLNode* nodoPajaros, int& pRojo,
			int& pVerde, int& pAzul);

	int tiempoGeneracionMinimo;
	int tiempoAcumulado;

	Simulador* simulador;

	ColaProtegida<Evento> colaMensajes;
};

#endif /* NIVELSERVER_H_ */
