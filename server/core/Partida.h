#ifndef PARTIDA_H_
#define PARTIDA_H_

enum EstadoPartida {
	CREANDO,
	EJECUTANDO,
	PAUSADO,
	FINALIZADO
};

class Partida {
public:
	Partida(unsigned int id);
	virtual ~Partida();

	bool finalizo();

	EstadoPartida getEstado();

private:
	unsigned int id;
//	nivel;

	EstadoPartida estado;
};

#endif /* PARTIDA_H_ */
