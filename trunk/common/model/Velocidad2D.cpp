// Header Include.
#include "Velocidad2D.h"

// C++ Library Includes.
#include <cstdlib>  // Para usar la funcion 'atof'
#include <sstream>

// Exceptions Includes.
#include "exceptions/ParserException.h"

Velocidad2D::Velocidad2D(const XMLNode* nodo) {
	this->hydrate(nodo);
}

XMLNode* Velocidad2D::serialize() {
	XMLNode* nodo = new XMLNode("Velocidad2D");
	std::ostringstream valX, valY;
	valX << this->x;
	valY << this->y;
	nodo->SetAttribute("x", valX.str());
	nodo->SetAttribute("y", valY.str());
	return nodo;
}

void Velocidad2D::hydrate(const XMLNode* nodo) {
	// Obtengo el nombre del nodo
	std::string nombre = nodo->ValueStr();
	/* Comparo el nombre obtenido con el que se requiere.
	 * Si no es igual, lanzo una excepcion.
	 */
	if (nombre.compare("Velocidad2D") != 0) {
		throw ParserException("El nodo Velocidad2D es incorrecto.");
	}
	// Verifico si contiene el atributo x. Si no lo posee, lanzo excepcion.
	if (nodo->Attribute("x") == 0) {
		throw ParserException("El nodo Velocidad2D no contiene el atributo 'x'.");
	}
	// Verifico si contiene el atributo y. Si no lo posee, lanzo excepcion.
	if (nodo->Attribute("y") == 0) {
		throw ParserException("El nodo Velocidad2D no contiene el atributo 'y'.");
	}
	// Obtengo el atributo x e y
	std::string atributoX = nodo->Attribute("x");
	std::string atributoY = nodo->Attribute("y");
	this->x = std::atof(atributoX.c_str());
	this->y = std::atof(atributoY.c_str());
}

void Velocidad2D::set(float x, float y) {
	this->x = x;
	this->y = y;
}

Velocidad2D Velocidad2D::operator -() const {
	Velocidad2D v;
	v.set(-x, -y);
	return v;
}

void Velocidad2D::operator += (const Velocidad2D& v) {
	x += v.x;
	y += v.y;
}

void Velocidad2D::operator -= (const Velocidad2D& v) {
	x -= v.x;
	y -= v.y;
}

void Velocidad2D::operator *= (float a) {
	x *= a;
	y *= a;
}

bool Velocidad2D::operator == (const Velocidad2D& v) {
	return (x == v.x && y == v.y);
}
