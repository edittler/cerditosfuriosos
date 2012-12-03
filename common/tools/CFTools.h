/*
 * Encabezado de herramientas de conversion de string a numeros enteros o
 * flotantes y viceversa.
 */

#ifndef CFTOOLS_H_
#define CFTOOLS_H_

#include <string>

namespace cft {

float stringToFloat(std::string cadena);

std::string floatToString(float valor);

int stringToInt(std::string cadena);

std::string intToString(int valor);

unsigned int stringToUint(std::string cadena);

std::string uintToString(unsigned int valor);
} /* namespace cft */
#endif /* CFTOOLS_H_ */
