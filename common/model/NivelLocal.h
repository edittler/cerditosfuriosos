#ifndef NIVELLOCAL_H_
#define NIVELLOCAL_H_

#include "Nivel.h"
#include "Simulador.h"

class NivelLocal: public Nivel {
    private:
        int tiempoGeneracionMinimo;
        int tiempoAcumulado;  
        
        Simulador* simulador;
    public:
		NivelLocal(Escenario* escenario, int tiempoGeneracionMinimo);
		virtual ~NivelLocal();

		void tick(int milisegundos);
		bool finalizoPartida();

		void generarPajaro();
		void lanzarHuevo(Punto2D posInicial, Velocidad2D velInicial, Jugador* jugador);
};

#endif
