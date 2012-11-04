#include <iostream>
#include "model/Escenario.h"

int main(int argc, char *argv[]) {
	Escenario escena;
	// Choque caja madera con pajaro y/o huevo
	escena.agregarCajaMadera(Punto2D(1,1));
	escena.agregarMonticulo(Punto2D(5, 5));
	escena.agregarCerdito(Punto2D(10, 5), Punto2D(15, 5));
	escena.habilitarSimulacion();
//	escena.lanzarPajaroRojo(Punto2D(1,3),Velocidad2D(0,-10));
	escena.lanzarHuevoBlanco(Punto2D(1,3),Velocidad2D(0,-10));
	escena.lanzarHuevoBlanco(Punto2D(5,10),Velocidad2D(0,-10));

	// choque en y de pajaro y huevo (en 4ta iteracion)
//	escena.lanzarPajaroRojo(Punto2D(10, 15), Velocidad2D(0, -20));
//	escena.lanzarHuevoBlanco(Punto2D(10, 12), Velocidad2D(0, 20));

	// choque de dos pajaros (en 5ta iteracion)
//	escena.lanzarPajaroRojo(Punto2D(5, 3), Velocidad2D(20, 30));
//	escena.lanzarPajaroRojo(Punto2D(9, 3), Velocidad2D(-20, 30));

	// restitucion - se calcula segun la velocidad y parametro de restitucion
//	escena.lanzarPajaroRojo(Punto2D(5, 2), Velocidad2D(0, -20));
//	escena.lanzarPajaroRojo(Punto2D(10, 0.9), Velocidad2D(0, 0));

	// choque con bordes (en 2ra iteracion)
//	escena.lanzarHuevoBlanco(Punto2D(5, 3), Velocidad2D(0, 10));
//	escena.lanzarPajaroRojo(Punto2D(5.1, 5), Velocidad2D(0, -10));

	for(int i = 0; i < 200; i++) {
		escena.correrTick();
		getchar();  // tecla para continuar.
	}

	return 0;
}
