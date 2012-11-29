// Standard C++ Library Includes
#include <iostream>
#include <cstdio>

// Common Project Includes.
#include "Log.h"

// Server Project Includes.
#include "core/Server.h"
#include "CFTools.h"

// Defines
#define OK 0
#define ERROR 1
#define TOTAL_PARAM 2

int main(int argc, char *argv[]) {
	if (argc != TOTAL_PARAM) {
		LOG_INFO("Indicar puerto.")
		return ERROR;
	}

	// Creo y configuro servidor.
	Server server(cft::stringToInt(argv[1]));
	if (!server.prender()) {
		LOG_INFO("Error al prender Server.")
		return ERROR;
	}

	LOG_INFO("Server prendido.")

	// logica para cerrar Server
	// puede hacerse igual que tp4 al ingresar 'q' se cierra el server.
	while (getchar() != 'q') { }

	server.apagar();
	LOG_INFO("Server apagado.")

	return OK;
}
