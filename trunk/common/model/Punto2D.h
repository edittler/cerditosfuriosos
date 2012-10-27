/* Punto 2D para ser manejado por la clase Escenario y usuarios.
 */

#ifndef PUNTO2D_H_
#define PUNTO2D_H_

struct Punto2D {
	// Constructor por default que se inicializa en (0,0).
	Punto2D() : x(0.0f), y(0.0f) { }

	// Constructor que inicializa con las coordenadas especificadas.
	Punto2D(float x, float y) : x(x), y(y) { }

	// Setea el punto con las coordenadas especificadas.
	void set(float x_, float y_) { x = x_; y = y_; }

	// Niega el punto.
	Punto2D operator -() const { Punto2D p; p.set(-x, -y); return p; }

	// Suma el punto con otro punto.
	void operator += (const Punto2D& p) { x += p.x; y += p.y; }

	// Resta el punto con otro punto.
	void operator -= (const Punto2D& p) { x -= p.x; y -= p.y; }

	// Multiplica el punto por un escalar.
	void operator *= (float32 a) { x *= a; y *= a; }

	// Coordenada X.
	float x;

	// Coordenada Y.
	float y;
};

#endif /* PUNTO2D_H_ */
