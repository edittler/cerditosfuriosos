#ifndef SIMULADOR_H_
#define SIMULADOR_H_

#include "Punto2D.h"
#include "Velocidad2D.h"

class Simulador {
public:
	/**
	 * Constructor que carga las probabilidades por default.
	 */
	Simulador();

	/**
	 * Constructor que carga las probabilidades especificadas por parametro.
	 */
	Simulador(int probGeneracion, int pRojo, int pVerde, int pAzul, float posX,
			float posYMinima, float posYMaxima);

	/**
	 * Destructor
	 */
	virtual ~Simulador();

	/**
	 * Genera un huevo, según valores dados por default.
	 * @return 1:HUEVO_BLANCO 2:HUEVO_CODORNIZ 3:HUEVO_POCHE 4:HUEVO_RELOJ
	 */
	int generarHuevo();

	/**
	 * @brief devuelve un identificador de pajaro segun las probabilidades
	 * establecidas para cada uno.
	 * @return 0: NO_PAJARO, 1: PAJARO_AZUL, 2: PAJARO_ROJO, 3: PAJARO_VERDE.
	 */
	int generarPajaro(Punto2D& punto, Velocidad2D& velocidad);

	/*
	 * @brief genera un ramdom del tipo float contenido entre dos
	 * limites.
	 * @param min limite inferior
	 * @param max limite superior
	 * @return random generado.
	 */
	float randomFloat(float min, float max);

private:
	Punto2D generarPosicion();
	Velocidad2D generarVelocidad();

	// Probabilidad de que se genere un pajaro
	int probabilidadGeneracion;

	// Probabilidad de que se genere un pajaro y su variedad
	int probabilidadPajaroAzul;
	int probabilidadPajaroRojo;
	int probabilidadPajaroVerde;

	// Posicion en el eje x
	float posX;
	// Posición minima y máxima en el eje y
	float posYminima, posYmaxima;
};

#endif
