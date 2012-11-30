// Header Include.
#include "Punto2D.h"

// C++ Library Includes.
#include <sstream>

// Exceptions Includes.
#include "exceptions/ParserException.h"

Punto2D::Punto2D(const XMLNode* nodo) {
	this->hydrate(nodo);
}

XMLNode* Punto2D::serialize() {
	XMLNode* nodo = new XMLNode("Punto2D");
	std::ostringstream valX, valY;
	valX << this->x;
	valY << this->y;
	nodo->SetAttribute("x", valX.str());
	nodo->SetAttribute("y", valY.str());
	return nodo;
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
	std::istringstream atributoX(nodo->Attribute("x"));
	std::istringstream atributoY(nodo->Attribute("y"));
	// Seteo la configuracion regional defaul de C++ para dichos streams.
	atributoX.imbue(std::locale("C"));
	atributoY.imbue(std::locale("C"));
	atributoX >> this->x;
	atributoY >> this->y;
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

bool Punto2D::operator == (const Punto2D& p) const {
	return (x == p.x && y == p.y);
}
