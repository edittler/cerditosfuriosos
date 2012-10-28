#ifndef PUNTAJE_H_
#define PUNTAJE_H_

/* Clase que administra puntos
 */
class Puntaje {
public:
	// Constructor
	Puntaje();

	// Destructor
	virtual ~Puntaje();

	/* Suma los puntos especificados.
	 * @param Puntos a sumar
	 * Nota: Puede ser un valor negativo, en caso que se requiera restar puntos.
	 */
	void sumarPuntos(int puntos);

	// @return Retorna la cantidad de puntos
	int getPuntos() const;

private:
	// Puntos
	int puntos;
};

#endif /* PUNTAJE_H_ */
