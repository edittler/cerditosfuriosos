#ifndef _INTERFAZ_SELECTORA_H_
#define _INTERFAZ_SELECTORA_H_

/**
 * Interfaz para que los distintos paneles informen cuando el usuario selecciona
 * distintas opciones.
 */
class InterfazSelectora {
	public:
	
		/**
		 * El usuario selecciono que desea jugar en modo un jugador.
		 */
		virtual void modoUnJugador() = 0;
		
		/**
		 * El usuario selecciono que desea jugar en modo multijugador.
		 */
		virtual void modoMultijugador() = 0;
		
		/**
		 * El usuario selecciono que quiere unirse a una partida ya creada.
		 */
		virtual void unirseAPartida() = 0;

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
};

#endif
