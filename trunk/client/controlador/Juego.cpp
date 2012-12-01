// Header Include.
#include "Juego.h"

// GTK+ Library Includes.
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>

// Client Project Includes.
#include "../modelo/NivelLocal.h"
#include "../modelo/NivelProxy.h"
#include "../vista/modelo/ConstantesVistaModelo.h"

Juego::Juego(VentanaPrincipal& ventana) : ventana(ventana) {
	this->ejecutando = true;
	this->local = true;
	this->mListener = NULL;
	this->nivel = NULL;
	this->vista = NULL;
	this->estado = SPLASH;
//	this->cliente = new Client(ventana, "127.0.0.1", 5558);
	this->cliente = new Client(ventana, "192.168.1.6", 5555);
	this->iniciarSenialesBotones();
}

Juego::~Juego() {
	if (cliente->conectado())
		cliente->desconectar();
	delete cliente;
}

void Juego::finalizarJuego() {
	this->ejecutando = false;
	if (cliente->conectado())
		this->cliente->desconectar();
}

void* Juego::run() {
	while (this->ejecutando) {
		switch (this->estado) {
		case SPLASH: {
			Gtk::Image imagen(SPLASH_IMAGEN);
			ventana.agregarContenedor(imagen);
			sleep(WAIT);
			ventana.mostrarMenuPrincipal();
			this->estado = MENU;
			break;
		}
		case MENU: {
			// Consulto al cliente si hay alguna partida corriendo
			if ((cliente->conectado()) && (cliente->corriendoPartida())) {
				// Si hay una partida corriendo, paso a modo GAMEINIT
				this->estado = GAMEINIT;
			}
			break;
		}
		case GAMEINIT: {
			this->iniciarPartida();
			this->estado = GAMEPLAY;
			break;
		}
		case GAMEPLAY: {
			while (!nivel->finalizoPartida() && this->ejecutando) {
				// Verifico si el cliente está conectado y corriendo la partida
				if ((cliente->conectado()) && (cliente->partidaPausada()))
					this->estado = GAMEPAUSE;
				this->nivel->tick(TIEMPO_TICK_MSEG);
//				usleep(DELTA_LOOP);
			}

			/* FIXME por ahora se puede correr un solo nivel.
			 * completar para que busque el siguiente nivel y lo cargue
			 */
			if (nivel->getEscenario()->ganoPartida())
				this->estado = GANO;
			else
				this->estado = PERDIO;

			this->mListener->borrarEventos();
			ventana.vaciarContenedor();
			delete this->vista;
			delete this->mListener;
			delete this->nivel;

			break;
		}
		case GAMEPAUSE: {
			// Si el cliente está conectado, consulto si se reanudó la partida.
			if (cliente->conectado()) {
				// Consultar si se reanudo la partida.
				if (cliente->corriendoPartida()) {
					/* Si la partida está corriendo, retorno al estado GAMEPLAY
					 * para seguir procesando evento
					 */
					this->estado = GAMEPLAY;
				}
			} else {
				// TODO analizar que se hace en estado local.
			}
			break;
		}
		case GANO: {
			Gtk::Image imagen(WIN_IMAGEN);
			ventana.agregarContenedor(imagen);
			sleep(WAIT);
			ventana.mostrarMenuPrincipal();
			this->estado = MENU;
			break;
		}
		case PERDIO: {
			Gtk::Image imagen(GAME_OVER_IMAGEN);
			ventana.agregarContenedor(imagen);
			sleep(WAIT);
			ventana.mostrarMenuPrincipal();
			this->estado = MENU;
			break;
		}
		case EXIT: {
			this->ejecutando = false;
			Gtk::Main::quit();
			break;
		}
		default:
			break;
		}  // Fin  switch
	}
	return NULL;
}

void Juego::iniciarSenialesBotones() {
	// Botones del menú principal
	ventana.panelInicial->botonMultijugador->signal_clicked().connect(
			sigc::mem_fun(*this, &Juego::botonMultijugador));
	ventana.panelInicial->botonSalir->signal_clicked().connect(
			sigc::mem_fun(*this, &Juego::botonSalir));
	// Botones del menú modo Un Jugador
	ventana.panelUnJugador->botonSeleccionar->signal_clicked().connect(
			sigc::mem_fun(*this, &Juego::botonUnJugador));
	// Botones del menú modo Multijugador
	ventana.panelMultijugador->botonCrearPartida->signal_clicked().connect(
			sigc::mem_fun(*cliente, &Client::botonCrearPartida));
	ventana.panelCrearPartida->botonCrear->signal_clicked().connect(
			sigc::mem_fun(*cliente, &Client::botonMundoSeleccionado));
	ventana.panelMultijugador->botonUnirsePartida->signal_clicked().connect(
			sigc::mem_fun(*cliente, &Client::botonUnirsePartida));
	ventana.panelUnirsePartida->botonSeleccionar->signal_clicked().connect(
			sigc::mem_fun(*cliente, &Client::botonPartidaSeleccionada));
	ventana.panelMultijugador->botonVolver->signal_clicked().connect(
			sigc::mem_fun(*this, &Juego::botonSalirModoMultijugador));
}

void Juego::iniciarPartida() {
	// Si el cliente no está conectado, instancio un nivel local
	if (!cliente->conectado()) {
		// Instancio un nivel local
		this->nivel = new NivelLocal();

		// Creo la vista y le asocio el escenario del modelo
		this->vista = new VistaEscenario(nivel->getEscenario());

		// hidrato escenario
		this->nivel->cargarXML(ventana.panelUnJugador->
				getRutaNivelSeleccionado());

		std::cout << "Obtengo la posicion de la catapulta\n";
		Punto2D p = nivel->getPosicionCatapulta(1);
		std::cout << "Seteo la posicion en el mouseListener\n";
		mListener = new MouseListener(*nivel, p.x, p.y + 0.4);
		// Inicio la vista
		ventana.agregarContenedor(*vista);
		ventana.setMouseListener(mListener);
	} else {
		// Instancio un nivel proxy
		this->nivel = new NivelProxy(cliente->getIDJugdor(),
				cliente->getSocket(), cliente->getColaEvento());

		// Creo la vistaEscenario y le asocio el escenario del modelo
		this->vista = new VistaEscenario(nivel->getEscenario());

		// hidrato escenario
		this->nivel->cargarXML(cliente->getRutaNivel());

		std::cout << "Obtengo la posicion de la catapulta\n";
		Punto2D p = nivel->getPosicionCatapulta(cliente->getIDJugdor());
		std::cout << "Seteo la posicion en el mouseListener\n";
		mListener = new MouseListener(*nivel, p.x, p.y + 0.4);
		// Inicio la vista
		ventana.agregarContenedor(*vista);
		ventana.setMouseListener(mListener);
	}
}

void Juego::botonUnJugador() {
	estado = GAMEINIT;

	/* FIXME Debo cargar un mapa de los niveles que posee el mundo y almacenar
	 * el numero de nivel elegido para que el gameloop ejecute el correcto.
	 * O la vista debe proveer métodos de consulta.
	 */
}

void Juego::botonMultijugador() {
	// Establezco el estado del juego como Multijugador
	this->local = false;
	// Conecta el cliente y verifico si se pudo conectar.
	bool conecto = cliente->conectar();
	/* Si el cliente se conecto, muestro el panel multijugador.
	 */
	if (conecto) {
		this->ventana.modoMultijugador();
	} else {
		/* Si el cliente no se pudo conectar, muestro un mensaje que lo indique
		 * y regreso al menu principal.
		 */
		// TODO mostrar mensaje y regresar al menu principal.
		ventana.mostrarDialogo("No es posible establecer una conexión con "
				"el servidor");
	}
}

void Juego::botonSalirModoMultijugador() {
	this->cliente->desconectar();
	this->ventana.volverAMenuPrincipal();
}

void Juego::botonSalir() {
	// Cambia el estado del juego a EXIT
	this->estado = EXIT;
}
