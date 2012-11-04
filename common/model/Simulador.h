#ifndef SIMULADOR_H_
#define SIMULADOR_H_

class Simulador {
	// Probabilidad de que se genere un pajaro y su variedad
	int probabilidadPajaroAzul;
	int probabilidadPajaroRojo;
	int probabilidadPajaroVerde;
public:
	Simulador(int pAzul, int pRojo, int pVerde);
	virtual ~Simulador();

	int generarPajaro();
};

#endif
