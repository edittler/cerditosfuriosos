#ifndef _INTERFAZ_SELECTORA_H_
#define _INTERFAZ_SELECTORA_H_

/**
 * Interfaz para que los distintos paneles informen cuando el usuario selecciona
 * distintas opciones.
 */
class InterfazSelectora {
public:
	/**
	 * Destructor Virtual
	 */
	virtual ~InterfazSelectora() { }
	
	/**
	 * El usuario selecciono que desea jugar en modo un jugador.
	 */
	virtual void modoUnJugador() = 0;

	/**
	 * El usuario selecciono que desea jugar en modo multijugador.
	 */
	virtual void modoMultijugador() = 0;

	/**
	 * El usuario selecciono que desea editar la configuracion del cliente.
	 */
	virtual void modoConfiguracion(std::string direccion,
			unsigned short int puerto) = 0;

	/**
	 * El usuario selecciono que quiere ver los records.
	 */
	virtual void verRecords() = 0;

	/**
	 * El usuario selecciono que desea volver al menu principal.
	 */
	virtual void volverAMenuPrincipal() = 0;

	/**
	 * El usuario selecciono que desea crear una partida.
	 * @param nombreMundos lista con los mundos entre los que puede
	 * seleccionar el usuario para crear una partida
	 */
	virtual void modoCrearPartida(std::string nombreMundos) = 0;

	/**
	 * El usuario selecciono que desea ver las partidas existentes.
	 * @param nombrePartidas lista con las partidas entre las que puede
	 * seleccionar el usuario para unirse
	 */
	virtual void modoUnirsePartida(std::string nombrePartidas) = 0;
};

#endif
