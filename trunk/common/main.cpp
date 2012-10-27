/*
 * main.cpp
 *
 *  Created on: 26/10/2012
 *      Author: ezequiel
 */
#include <iostream>
#include "model/Escenario.h"
#include "model/Colisionador.h"

int main(int argc, char *argv[]) {
	Escenario escena;
	escena.registrarContactListener(new Colisionador());
//	escena.agregarCajaMadera(1,1);

	// choque en y de pajaro y huevo (en 4ta iteracion)
//	escena.lanzarPajaroRojo(10, 15, 0, -20);
//	escena.lanzarHuevoBlanco(10, 12, 0, 20);

	// choque de dos pajaros (en 5ta iteracion)
	escena.lanzarPajaroRojo(5, 3, 20, 30);
	escena.lanzarPajaroRojo(9, 3, -20, 30);

	// restitucion - se calcula segun la velocidad y parametro de restitucion
//	escena.lanzarPajaroRojo(5, 2, 0, -20);
//	escena.lanzarPajaroRojo(10, 0.9, 0, 0);

	// choque con bordes (en 2ra iteracion)
//	escena.lanzarHuevoBlanco(5, 3, 0, 10);
//	escena.lanzarPajaroRojo(5.5, 5, 0, -10);

	for(int i = 0; i < 200; i++) {
		escena.correrTick();
		getchar();  // tecla para continuar.
	}

	return 0;
}


