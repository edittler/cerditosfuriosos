/* Velocidad 2D para ser manejado por la clase Escenario y usuarios.
 */

#ifndef VELOCIDAD2D_H_
#define VELOCIDAD2D_H_

struct Velocidad2D {
	// Constructor por default que se inicializa con velocidad nula.
	Velocidad2D() : x(0.0f), y(0.0f) { }

	// Constructor que inicializa con las velocidades especificadas.
	Velocidad2D(float x, float y) : x(x), y(y) { }

	// Setea el vector con las velocidades especificadas.
	void set(float x_, float y_) { x = x_; y = y_; }

	// Niega las magnitudes de la velocidad.
	Velocidad2D operator -() const { Velocidad2D v; v.set(-x, -y); return v; }

	// Suma el vector con otro vector de velocidad.
	void operator += (const Velocidad2D& v) { x += v.x; y += v.y; }

	// Resta el vector con otro vector de velocidad.
	void operator -= (const Velocidad2D& v) { x -= v.x; y -= v.y; }

	// Multiplica el vector de velocidad por un escalar.
	void operator *= (float a) { x *= a; y *= a; }

	// Compara dos velocidades.
	bool operator == (const Velocidad2D& v) { return (x == v.x && y == v.y); }

	// Velocidad en eje X.
	float x;

	// Velocidad en eje Y.
	float y;
};

#endif /* VELOCIDAD2D_H_ */
