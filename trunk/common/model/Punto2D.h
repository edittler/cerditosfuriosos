#ifndef PUNTO2D_H_
#define PUNTO2D_H_

// Hierarchy Includes.
#include "../parser/Serializable.h"

class Punto2D: public Serializable {
public:
	// Constructor por default que se inicializa en (0,0).
	Punto2D() : x(0.0f), y(0.0f) { }

	// Constructor que inicializa con las coordenadas especificadas.
	Punto2D(float x, float y) : x(x), y(y) { }

	// Constructor que inicializa con las coordenadas a partir de un nodo XML.
	Punto2D(const XMLNode* nodo);

	// Destructor
	~Punto2D() { }

	// Serializa el Punto2D y retorna un nodo XML
	XMLNode* serialize();

	// A partir de un nodo XML se establece el Punto2D
	void hydrate(const XMLNode* nodo);

	// Setea el punto con las coordenadas especificadas.
	void set(float x_, float y_);

	// Niega el punto.
	Punto2D operator -() const;

	// Suma el punto con otro punto.
	void operator += (const Punto2D& p);

	// Resta el punto con otro punto.
	void operator -= (const Punto2D& p);

	// Multiplica el punto por un escalar.
	void operator *= (float a);

	// Compara dos Puntos2D.
	bool operator == (const Punto2D& p);

	// Coordenada X.
	float x;

	// Coordenada Y.
	float y;
};

#endif  /* PUNTO2D_H_ */
