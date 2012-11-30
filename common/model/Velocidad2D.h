#ifndef VELOCIDAD2D_H_
#define VELOCIDAD2D_H_

// Hierarchy Includes.
#include "../parser/Serializable.h"

class Velocidad2D: public Serializable {
public:
	// Constructor por default que se inicializa en (0,0).
	Velocidad2D() : x(0.0f), y(0.0f) { }

	// Constructor que inicializa con las velocidades especificadas.
	Velocidad2D(float x, float y) : x(x), y(y) { }

	// Constructor que inicializa con las velocidades a partir de un nodo XML.
	explicit Velocidad2D(const XMLNode* nodo);

	// Destructor
	~Velocidad2D() { }

	// Serializa la Velocidad2D y retorna un nodo XML
	XMLNode* serialize();

	// A partir de un nodo XML se establece la Velocidad2D
	void hydrate(const XMLNode* nodo);

	// Setea la velocidad con las velocidades especificadas.
	void set(float x_, float y_);

	// Niega la velocidad.
	Velocidad2D operator -() const;

	// Suma la velocidad con otro punto.
	void operator += (const Velocidad2D& v);

	// Resta la velocidad con otro punto.
	void operator -= (const Velocidad2D& v);

	// Multiplica la velocidad por un escalar.
	void operator *= (float a);

	// Compara dos Velocidad2D.
	bool operator == (const Velocidad2D& v) const;

	// Velocidad en el eje X.
	float x;

	// Velocidad en el eje Y.
	float y;
};

#endif /* VELOCIDAD2D_H_ */
