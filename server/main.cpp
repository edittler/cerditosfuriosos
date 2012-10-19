/* Aplicación del servidor
 *
 */

// Standard C++ Library Includes
#include <iostream>

// Project Includes
#include "../common/thread/Mutex.h"

int main(int argc, char *argv[]) {
	std::cout << "Soy el Servidor!!" << std::endl;

	Mutex unMutex;

	return 0;
}


