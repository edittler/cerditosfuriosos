// Header Include.
#include "Juego.h"

// GTK+ Library Includes.
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>

// Client Project Includes.
#include "../modelo/NivelLocal.h"
#include "../vista/modelo/ConstantesVistaModelo.h"

Juego::Juego(VentanaPrincipal& ventana) : ventana(ventana) {
	this->ejecutando = true;
	this->local = true;
	this->nivel = NULL;
	this->vista = NULL;
	this->estado = SPLASH;
	this->inicialSenialesBotones();
}

Juego::~Juego() { }

void Juego::finalizarJuego() {
	this->ejecutando = false;
}

void* Juego::run() {
	while (this->ejecutando) {
		switch (this->estado) {
		case SPLASH: {
			Gtk::Image imagen(SPLASH_IMAGEN);
			ventana.agregarContenedor(imagen);
			sleep(WAIT);
			ventana.volverAMenuPrincipal();
			this->estado = MENU;
			break; }
		case MENU: {
			break; }
		case GAMEPLAY: {
			// Instancio un nivel local
			this->nivel = new NivelLocal();

			// Creo la vista y le asocio el escenario del modelo
			this->vista = new VistaEscenario(nivel->getEscenario());

			// hidrato escenario
			this->nivel->cargarXML("../common/MiMundo-level1.xml");

			std::cout << "Obtengo la posicion de la catapulta\n";
			Punto2D p = nivel->getPosicionCatapulta(1);
			std::cout << "Seteo la posicion en el mouseListener\n";
			MouseListener mListener(*nivel, p.x, p.y + 0.4);
			// Inicio la vista
			ventana.agregarContenedor(*vista);
			ventana.setMouseListener(&mListener);

			int i = 0;
			while (!nivel->finalizoPartida() && this->ejecutando) {
				this->nivel->tick(TIEMPO_TICK_MSEG);
				std::cout << "tick " << i++ << std::endl;
				usleep(DELTA_LOOP);
			}

			if (nivel->getEscenario()->ganoPartida())
				this->estado = GANO;
			else
				this->estado = PERDIO;

			delete this->vista;
			delete this->nivel;

			break; }
		case GANO: {
			Gtk::Image imagen(WIN_IMAGEN);
			ventana.agregarContenedor(imagen);
			sleep(WAIT);
			ventana.volverAMenuPrincipal();
			this->estado = MENU;
			break; }
		case PERDIO: {
			Gtk::Image imagen(GAME_OVER_IMAGEN);
			ventana.agregarContenedor(imagen);
			sleep(WAIT);
			ventana.volverAMenuPrincipal();
			this->estado = MENU;
			break; }
		case EXIT: {
			this->ejecutando = false;
			Gtk::Main::quit();
			break; }
		default:
			break;
		}
	}
	return NULL;
}

void Juego::inicialSenialesBotones() {
	ventana.panelUnJugador->botonSeleccionar->signal_clicked().connect(
			sigc::mem_fun(*this, &Juego::botonUnJugador));
}

void Juego::botonUnJugador() {
	/* FIXME se debe poder seleccionar el mundo elegido y el numero de nivel.
	 */
	//	std::string rutaNivelSeleccionado = ventana->panelUnJugador->
	//													getRutaNivelSeleccionado();
	estado = GAMEPLAY;

	/* TODO Cargo un mapa de los niveles que posee el mundo y almaceno el numero
	 * de nivel elegido para que el gameloop ejecute el correcto.
	 */
}

void Juego::botonMultijugador() {
	// Establezco el estado del juego como Multijugador
	this->local = false;
	// Conecta el cliente y... TODO Implementar!
}

void Juego::botonSalir() {
	// Cambia el estado del juego a EXIT
	this->estado = EXIT;
}
