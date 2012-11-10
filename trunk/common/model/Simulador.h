#ifndef SIMULADOR_H_
#define SIMULADOR_H_

class Simulador {
protected:
	// Probabilidad de que se genere un pajaro y su variedad
	int probabilidadPajaroAzul;
	int probabilidadPajaroRojo;
	int probabilidadPajaroVerde;
public:
	Simulador(int pAzul, int pRojo, int pVerde);
	virtual ~Simulador();

	int generarPajaro();
	int generarAlturaPajaro(int alturaMin, int alturaMax);
};

#endif
