// Standard C++ Library Includes
#include <iostream>

#include "Server.h"
#include "ThreadListener.h"
#include <cstdio>

int main(int argc, char *argv[]) {
	std::cout << "Soy el Servidor!!" << std::endl;

	// Creo y configuro servidor.
	Server* server = new Server(5555);
	server->prender();

	// Creo ThreadListener y comienzo Thread.
	ThreadListener* listener =  new ThreadListener(server);
	listener->start();

	// logica para cerrar Server
	// puede hacerse igual que tp4 al ingresar 'q' se cierra el server.
	while (getchar() != 'q') { }

	return 0;
}


