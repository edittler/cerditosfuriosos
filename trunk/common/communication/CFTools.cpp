// Header Include.
#include "CFTools.h"

// C++ Library Includes.
#include <sstream>

namespace cft {

float stringToFloat(std::string cadena) {
	std::istringstream val(cadena);
	val.imbue(std::locale("C"));
	float valor;
	val >> valor;
	return valor;
}

std::string floatToString(float valor) {
	std::ostringstream val;
	val.imbue(std::locale("C"));
	val << valor;
	return val.str();
}

int stringToInt(std::string cadena) {
	std::istringstream val(cadena);
	val.imbue(std::locale("C"));
	int valor;
	val >> valor;
	return valor;
}

std::string intToString(int valor) {
	std::ostringstream val;
	val.imbue(std::locale("C"));
	val << valor;
	return val.str();
}

unsigned int stringToUint(std::string cadena) {
	std::istringstream val(cadena);
	val.imbue(std::locale("C"));
	unsigned int valor;
	val >> valor;
	return valor;
}

std::string uintToString(unsigned int valor) {
	std::ostringstream val;
	val.imbue(std::locale("C"));
	val << valor;
	return val.str();
}

} /* namespace cft */
