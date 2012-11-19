// Header Include.
#include "CFDTools.h"

// C++ Library Includes.
#include <sstream>

namespace cfd {

float stringToFloat(std::string cadena) {
	std::istringstream val(cadena);
	val.imbue(std::locale("C"));
	float valor;
	val >> valor;
	return valor;
}

int stringToInt(std::string cadena) {
	std::istringstream val(cadena);
	val.imbue(std::locale("C"));
	int valor;
	val >> valor;
	return valor;
}

std::string floatToString(float valor) {
	std::ostringstream val;
	val.imbue(std::locale("C"));
	val << valor;
	return val.str();
}

std::string intToString(int valor) {
	std::ostringstream val;
	val.imbue(std::locale("C"));
	val << valor;
	return val.str();
}

} /* namespace cfd */
