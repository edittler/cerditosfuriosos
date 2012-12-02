#ifndef CLIENT_H_
#define CLIENT_H_

// Common Project Includes.
#include "../../common/communication/Socket.h"
#include "../../common/communication/ColaProtegida.h"
#include "../../common/communication/Evento.h"
#include "../../common/thread/Thread.h"
#include "../../common/thread/Mutex.h"

// Client Project Includes.
#include "../vista/menues/VentanaPrincipal.h"

/**
 * Cliente
 * Clase que implementa la logica de comunicaciones con el servidor en el modo
 * multijugador del juego.
 */
class Client : public Thread{
public:
	/**
	 * Constructor por default
	 * Se conecta al servidor mediante la dirección IP de loopback (localhost)
	 * y el puerto por default establecido por el server desarrollado.
	 */
	Client(VentanaPrincipal& ventana);

	/**
	 * Destructor
	 */
	virtual ~Client();

	/**
	 * Se conecta al servidor.
	 * @return Retorna true si se pudo conectar con el server o false en caso
	 * contrario.
	 */
	bool conectar();

	/**
	 * Cierra conexion con el servidor en forma ordenada mediante el método
	 * shutdown.
	 */
	void desconectar();

	/**
	 * Retorna un puntero del socket
	 * @return puntero del socket usado para conexiones.
	 */
	Socket& getSocket() const;

	/**
	 * Retorna el ID del jugador que le fue asignado al cliente.
	 * @return ID del jugador
	 */
	unsigned int getIDJugdor() const;

	/**
	 * Retorna la cola de eventos.
	 */
	ColaProtegida<Evento>& getColaEvento();

	/**
	 * Retorna la ruta donde está almacenados los datos del nivel
	 */
	std::string getRutaNivel() const;

	/**
	 * Retorna el estado de conexion del cliente.
	 * @return true si el cliente está conectado, false en caso contrario.
	 */
	bool conectado() const;

	/**
	 * Retorna el estado de la partida, si es que se inició una.
	 * @return true si la partida esta corriendo, false en caso contrario.
	 */
	bool corriendoPartida();

	/**
	 * Retorna el estado de pausa de la partida, si es que se inició una.
	 * @return true si la partida está pausada, false en caso contrario.
	 */
	bool partidaPausada();

	/**
	 * Retorna el estado finalizacion de la partida, si es que se inició una.
	 * @return true si la partida finalizó, false en caso contrario.
	 */
	bool partidaFinalizada();

	/**
	 * Metodo que se llama al seleccionar el botón para editar la configuracion.
	 */
	void botonConfiguracion();

	/**
	 * Metodo que se llama al seleccionar el botón para guardar la
	 * configuracion.
	 */
	void botonGuardarConfiguracion();

	/**
	 * Metodo que se llama al seleccionar el botón para crear una partida.
	 * Envía un mensaje al servidor solicitando los mundos disponibles y los
	 * lista por pantalla.
	 */
	void botonCrearPartida();

	/**
	 * Método que se llama al haber seleccionado un mundo para crear la partida.
	 * Consulta a la vista cual es el mundo seleccionado y el nombre elegido.
	 * Envía un mensaje al servidor solicitando la creación de la partida
	 * con las caracteristicas deseadas por el usuario.
	 */
	void botonMundoSeleccionado();

	/**
	 * Método que se llama al seleccionar el botón para unirse a una partida.
	 * Envía un mensaje al servidor solicitando las partidas disponibles para
	 * unirse y los lista por pantalla.
	 */
	void botonUnirsePartida();

	/**
	 * Método que se llama al haber seleccionado una partida a la cual unirse.
	 * Envía al servidor el pedido de unirse a la partida. En caso de que se
	 * confirme su incorporación, corre en un thread la recepción de mensajes
	 * del servidor. Si fallo su incorporación, retorna a la pantalla
	 * multijugador.
	 */
	void botonPartidaSeleccionada();

	/**
	 * Método que se llama al seleccionar el botón para ver los records.
	 * Envía un mensaje al servidor solicitando los records y
	 * los lista por pantalla.
	 */
	void botonVerRecords();

	/**
	 * Método que se llama al seleccionar la opción de Abandonar Partida.
	 * Envía un mensaje al servidor avisando que abandona la partida y regresa
	 * a la pantalla multijugador.
	 */
	void botonAbandonarPartida();

protected:
	/**
	 * Método que se corre mientras sea necesario recibir mensajes del servidor
	 * cuando se está ejecutando una partida.
	 */
	void* run();

private:
	/**
	 * Carga la configuracion a partid de un archivo de configuracion
	 */
	void cargarConfiguracion();

	/**
	 * Almacena los datos XML del nivel en un archivo temporal.
	 * @param string con el xml serializado
	 */
	void guardarXML(std::string datosXMLNivel) const;

	// Socket mediante el cual se realizan las comunicaciones con el server.
	Socket* socket;

	// Puerto mendiante el cual se realizan las comunicaciones.
	Puerto port;

	// Referencia de la ventana donde se muestra la info recibida
	VentanaPrincipal& ventana;

	// Dirección IP del server.
	std::string serverIp;

	// ID del jugador que es asignado al cliente.
	unsigned int idJugador;

	// Booleano que especifica si la partida está corriendo o pausada
	bool _corriendoPartida;

	// Booleano que especifica si la partida finalizo
	bool _partidaFinalizada;

	// Cola de eventos
	ColaProtegida<Evento> colaEventos;

	/* Mutex para protejer los accesos a booleanos de consulta de estado de
	 * partida.
	 */
	Mutex mBoolsPartida;

	// Ruta de archivo XML donde se almacena el nivel recibido desde el server.
	std::string rutaNivelRecibido;
};

#endif /* CLIENT_H_ */
