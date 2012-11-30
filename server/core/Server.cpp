// Header Include.
#include "Server.h"

// C++ Library Includes.
#include <stdexcept>

// Common Project Includes.
#include "CFTools.h"
#include "Log.h"

// Server Project Includes.
#include "../modelo/ConstantesServer.h"

Server::Server() {
	this->encendido = false;
	this->socket = new Socket(PUERTO_DEFAULT);
}

Server::Server(Puerto port) {
	this->encendido = false;
	this->socket = new Socket(port);
}

Server::~Server() {
	// Si el servidor aún está encendido, lo apago
	if (this->encendido)
		this->apagar();
	delete socket;
}

bool Server::prender() {
	// Habilito el socket para conectarse y escuchar conexiones.
	socket->enlazar();
	socket->escucharConexiones(MAX_CONEXION_ESPERA);

	// si el puerto esta ocupado no prende el server
	if (!socket->estaEnlazado()) {
		LOG_INFO("error en enlazado, puerto ocupado")
		return false;
	}

	// Establezco que el servidor está encendido.
	encendido = true;

	// carga paths de xmls de mundos diponibles
	cargarInformacionMundos();

	// Comienzo el thread para aceptar clientes
	this->start();
	return true;
}

void Server::apagar() {
	// Establezco que el servidor está apagado
	encendido = false;
	// Desconecto el socket del servidor
	socket->desconectar();

	// Finalizo thread partidas
	PartidasDisponibles::iterator itPa;
	for (itPa = partidasDisponibles.begin(); itPa != partidasDisponibles.end(); ++ itPa) {
		itPa->second->finalizarEjecucion();
		itPa->second->join();
		delete itPa->second;
	}

	// Finalizo thread clientes
	ClientesConectados::iterator itCl;
	for (itCl = clientesConectados.begin(); itCl != clientesConectados.end(); ++itCl) {
		(*itCl)->finalizar();
		(*itCl)->join();
		delete (*itCl);
	}

	this->join();
}

void Server::crearPartida(Partida* partida, ThreadCliente* cliente) {
	ThreadPartida* tPartida = new ThreadPartida(partida, cliente);

	std::pair<unsigned int, ThreadPartida*> p(partida->getId(), tPartida);
	this->partidasDisponibles.insert(p);
	cliente->setPartida(tPartida);

	tPartida->start();
}

bool Server::unirseAPartida(unsigned int idPartida, ThreadCliente* cliente) {
	ThreadPartida* partida = NULL;
	try {  // valido que sea un idPartida valido
		partida = this->partidasDisponibles.at(idPartida);
	} catch (std::out_of_range& e) {
		return false;
	}
	return partida->unirseAPartida(cliente);
}

std::list<std::string> Server::getMundosDisponibles() const {
	std::list<std::string> list;
	MundosDisponibles::const_iterator it;
	for (it = mundosDiponibles.begin(); it != mundosDiponibles.end(); ++it) {
		list.push_back(it->first);
	}
	return list;
}

std::string Server::getPathXMLMundo(std::string id) const {
	return this->mundosDiponibles.at(id);
}

std::list<std::string> Server::getPartidasDisponibles() const {
	std::list<std::string> list;
	PartidasDisponibles::const_iterator it;
	for (it = partidasDisponibles.begin(); it != partidasDisponibles.end(); ++it) {
		std::string nombre = cft::intToString(it->first) + ": " + it->second->getNombrePartida();
		list.push_back(nombre);
	}
	return list;
}

ListaRecords Server::getTablaRecords(std::string nivel) {
	return this->records.at(nivel);
}

bool Server::eliminarClienteConectado(ThreadCliente* cliente) {
	ClientesConectados::iterator it;
	for (it = clientesConectados.begin(); it != clientesConectados.end(); ++it) {
		if ((*it) == cliente) {  // FIXME funciona correctamente si comparo punteros?
			clientesConectados.remove(cliente);
			delete cliente;
			return true;
		}
	}
	return false;
}

void Server::cargarInformacionMundos() {
	/* En el directorio donde se encuentra el ejecutable, se almacenará un
	 * archivo donde se encuentran todos los mundos que ha creado el diseñador.
	 * Ese archivo se llamará "mundos.xml"
	 */
	XMLDocument doc;
	bool seAbrio = doc.LoadFile(SERVER_RUTA_MUNDOS);
	// Si el archivo no existe, lo creo y salgo sin cargar mundos
	if (!seAbrio) {
		this->crearArchivoMundos();
		return;
	}

	// Obtengo el nodo raiz
	XMLNode* root = doc.RootElement();
	// Si es nulo, salgo sin realizar nada
	if (root == 0)
		return;

	// Obtengo el primer nodo del mundo
	const XMLNode* nodoMundo = root->FirstChildElement("Mundo");
	// Mientras el nodo de mundo no es nulo, cargo los mundos.
	while (nodoMundo != 0) {
		// Obtengo el nodo con el nombre del Mundo.
		const XMLNode* nodoNombre = nodoMundo->FirstChildElement("Nombre");
		std::string nombreMundo = nodoNombre->GetText();
		// Obtengo el atributo de la cantidad de jugadores
		int cantJugadores;
		const char* aCJ = nodoMundo->Attribute("cantJugadores", &cantJugadores);
		if (aCJ != 0) {
			std::string sCantJug = cft::intToString(cantJugadores);
			nombreMundo += " (" + sCantJug;
			// Si la cantidad de jugadores es 1
			if (cantJugadores == 1) {
				nombreMundo += " jugador)";
			} else {
				nombreMundo += " jugadores)";
			}
		}
		// Obtengo el nodo con la ruta de archivo del mundo.
		const XMLNode* nodoRuta = nodoMundo->FirstChildElement("Ruta");
		// Si los nodos no son nulos, cargo el mundo a la tabla
		if ((nodoNombre != 0) && (nodoRuta != 0)) {
			this->mundosDiponibles[nombreMundo] = nodoRuta->GetText();
		}
		// Obtengo el siguiente nodo Mundo
		nodoMundo = nodoMundo->NextSiblingElement("Mundo");
	}
}

void Server::crearArchivoMundos() {
	// Creo el nodo Mundos
	XMLNode* nodoMundos = new XMLNode("Mundos");
	// Creo un Documento y guardo el archivo.
	XMLDocument doc;
	XMLDeclaration* decl = new XMLDeclaration("1.0", "UTF-8", "");
	doc.LinkEndChild(decl);
	doc.LinkEndChild(nodoMundos);
	doc.SaveFile(SERVER_RUTA_MUNDOS);
}

void* Server::run() {
	while (this->encendido) {
		Socket* socket = this->socket->aceptarConexion();

		if (socket == NULL)
			continue;

		LOG_INFO("Se conecto un cliente...")

		ThreadCliente* cliente = new ThreadCliente(*this, socket);
		this->clientesConectados.push_back(cliente);
		cliente->start();
	}
	return NULL;
}
