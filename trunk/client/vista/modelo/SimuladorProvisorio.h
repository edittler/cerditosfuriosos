#ifndef SIMULADORPROVISORIO_H_
#define SIMULADORPROVISORIO_H_

#include <../../common/thread/Thread.h>
#include <Escenario.h>

class SimuladorProvisorio: public Thread {
public:
	SimuladorProvisorio(Escenario* escenario);
	virtual ~SimuladorProvisorio();

	void* run();
private:
	Escenario* escenario;
};

#endif /* SIMULADORPROVISORIO_H_ */
