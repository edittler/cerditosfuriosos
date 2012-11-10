#ifndef SIMULADORPROVISORIO_H_
#define SIMULADORPROVISORIO_H_

#include <unistd.h>

#include <../../common/thread/Thread.h>
#include <Escenario.h>
#include <Nivel.h>

class Juego: public Thread {
public:
	Juego(Escenario* escenario);
	virtual ~Juego();

	void* run();
private:
        Nivel* nivel;
};

#endif
