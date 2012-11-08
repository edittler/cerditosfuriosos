#ifndef SIMULADORPROVISORIO_H_
#define SIMULADORPROVISORIO_H_

#include <unistd.h>

#include <../../common/thread/Thread.h>
#include <Escenario.h>
#include <Nivel.h>

class SimuladorProvisorio: public Thread {
public:
	SimuladorProvisorio(Escenario* escenario);
	virtual ~SimuladorProvisorio();

	void* run();
private:
        Nivel* nivel;
};

#endif
