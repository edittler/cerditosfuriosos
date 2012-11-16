/*
 * Definiciones de tipos que utiliza el servidor.
 */

#ifndef DEFINICIONESSERVIDOR_H_
#define DEFINICIONESSERVIDOR_H_

// C++ Library Includes.
#include <list>
#include <map>
#include <utility>
#include <string>

// Forward Class Declarations.
class ThreadCliente;
class ThreadPartida;

// Lista de records logrados para un Mundo.
typedef std::list<std::pair<std::string, unsigned int> > ListaRecords;

// Tabla de records logrados
typedef std::map<std::string, ListaRecords> TablaRecords;

// Lista de clientes conectados
typedef std::list<ThreadCliente*> ClientesConectados;

// Mapa de Partidas disponibles
/**
 * FIXME El ID de la partida se debería cambiar por un string para poder
 * serializarse
 */
typedef std::map<unsigned int, ThreadPartida* > PartidasDisponibles;

#endif /* DEFINICIONESSERVIDOR_H_ */
