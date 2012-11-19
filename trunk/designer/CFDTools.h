/*
 * Encabezado de herramientas de conversion de string a numeros enteros o
 * flotantes y viceversa.
 */

#ifndef CFDTOOLS_H_
#define CFDTOOLS_H_

#include <string>

namespace cfd {

float stringToFloat(std::string cadena);

int stringToInt(std::string cadena);

std::string floatToString(float valor);

std::string intToString(int valor);

} /* namespace cfd */
#endif /* CFDTOOLS_H_ */
