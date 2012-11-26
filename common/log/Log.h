#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <cstdio>

#define LOG_INFO(mensaje) std::cout << "INFO - \t" << __FILE__ << ": " << mensaje << std::endl;

#endif /* LOG_H_ */
