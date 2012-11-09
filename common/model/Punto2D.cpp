// Header Include.
#include "Punto2D.h"

// C++ Library Includes.
#include <cstdlib>  // Para usar la funcion 'atof'

// Exceptions Includes.
#include "exceptions/ParserException.h"

Punto2D::Punto2D(const XMLNode* nodo) {
	this->hydrate(nodo);
}

XMLNode* Punto2D::serialize() {
	// TODO(eze) XML IMPLEMENTAR
	return 0;
}

void Punto2D::hydrate(const XMLNode* nodo) {
	// Obtengo el nombre del nodo
	std::string nombre = nodo->ValueStr();
	/* Comparo el nombre obtenido con el que se requiere.
	 * Si no es igual, lanzo una excepcion.
	 */
	if (nombre.compare("Punto2D") != 0) {
		throw ParserException("El nodo Punto2D es incorrecto.");
	}
	// Verifico si contiene el atributo x. Si no lo posee, lanzo excepcion.
	if (nodo->Attribute("x") == 0) {
		throw ParserException("El nodo Punto2D no contiene el atributo 'x'.");
	}
	// Verifico si contiene el atributo y. Si no lo posee, lanzo excepcion.
	if (nodo->Attribute("y") == 0) {
		throw ParserException("El nodo Punto2D no contiene el atributo 'y'.");
	}
	// Obtengo el atributo x e y
	std::string atributoX = nodo->Attribute("x");
	std::string atributoY = nodo->Attribute("y");
	this->x = std::atof(atributoX.c_str());
	this->y = std::atof(atributoY.c_str());
}

void Punto2D::set(float x, float y) {
	this->x = x;
	this->y = y;
}

Punto2D Punto2D::operator -() const {
	Punto2D p;
	p.set(-x, -y);
	return p;
}

void Punto2D::operator += (const Punto2D& p) {
	x += p.x;
	y += p.y;
}

void Punto2D::operator -= (const Punto2D& p) {
	x -= p.x;
	y -= p.y;
}

void Punto2D::operator *= (float a) {
	x *= a;
	y *= a;
}
