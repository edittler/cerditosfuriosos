#ifndef SIMULADOR_H_
#define SIMULADOR_H_

class Simulador {
public:
	Simulador(int pAzul, int pRojo, int pVerde);
	virtual ~Simulador();

	int generarHuevo();

	/*
	 * @brief devuelve un identificador de pajaro segun las probabilidades
	 * establecidas para cada uno.
	 * @return 0: NO_PAJARO, 1: PAJARO_AZUL, 2: PAJARO_ROJO, 3: PAJARO_VERDE.
	 */
	int generarPajaro();

	/*
	 * @brief genera un ramdom del tipo float contenido entre dos
	 * limites.
	 * @param min limite inferior
	 * @param max limite superior
	 * @return random generado.
	 */
	float randomFloat(float min, float max);

protected:
	// Probabilidad de que se genere un pajaro y su variedad
	int probabilidadPajaroAzul;
	int probabilidadPajaroRojo;
	int probabilidadPajaroVerde;
};

#endif
