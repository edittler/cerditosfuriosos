// Standard C++ Library Includes
#include <iostream>
#include <cstdio>

// Common Project Includes.
#include "Log.h"

// Server Project Includes.
#include "core/Server.h"

int main(int argc, char *argv[]) {
	// Creo y configuro servidor.
	Server server(5555);
	if (!server.prender()) {
		LOG_INFO("Error al prender Server.")
		return 1;
	}

	LOG_INFO("Server prendido.")

	// logica para cerrar Server
	// puede hacerse igual que tp4 al ingresar 'q' se cierra el server.
	while (getchar() != 'q') { }

	server.apagar();
	LOG_INFO("Server apagado.")

	return 0;
}


