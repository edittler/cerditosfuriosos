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
            void generarPajaro();
};

#endif
