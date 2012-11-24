#ifndef _PANEL_UN_JUGADOR_H_
#define _PANEL_UN_JUGADOR_H_

#include <gtkmm/label.h>

#include "PanelImagenFondo.h"
#include "SeleccionadorMultiple.h"
#include "InterfazSelectora.h"

// Constantes del layout y tamanio de los selectores
#define X_SELECTOR_MUNDOS 25
#define X_SELECTOR_NIVELES 250
#define Y_SELECTORES 200
#define ANCHO_SELECTORES 200
#define ALTO_SELECTORES 250
// Constantes de layout y tamanio del boton seleccionar
#define X_BOTON_SELECCIONAR 475
#define Y_BOTON_SELECCIONAR 300
#define ANCHO_BOTON_SELECCIONAR 100
#define ALTO_BOTON_SELECCIONAR 50
// Constantes de layout del boton volver
#define X_BOTON_VOLVER 25
#define Y_BOTON_VOLVER 550
// Constantes de layout y tamanio de las etiquetas
#define X_ETIQUETA_MUNDOS 25
#define X_ETIQUETA_NIVELES 250
#define Y_ETIQUETAS 150

/**
 * Muestra al usuario dos ventanas desplazables que le permiten elegir un mundo
 * y un nivel para jugar.
 */
class PanelUnJugador : public PanelImagenFondo {
public:

	/**
	 * Constructor.
	 */
	PanelUnJugador(int ancho,
			int alto,
			string ruta,
			InterfazSelectora* interfaz);

	/**
	 * Destructor.
	 */
	virtual ~PanelUnJugador();
	

	std::string getRutaNivelSeleccionado() const;


	Gtk::Button* botonSeleccionar;

private:

	/**
	 * El boton de seleccionar ha sido clickeado.
	 */
	void botonSeleccionarClickeado();

	/**
	 * Carga los nombres de los mundos y la ruta de los archivos
	 * correspondientes en un mapa.
	 */
	void cargarMundos();

	/**
	 * Carga los id de los niveles de un mundo y la ruta de los archivos
	 * correspondientes en un mapa.
	 * @param ruta ruta del mundo cuyos niveles queremos cargar
	 */
	void cargarNiveles(string ruta);

	/**
	 * Vacia el mapa de niveles para introducir los correspondientes a un
	 * mundo distinto.
	 */
	void vaciarMapaNiveles();

	/**
	 * Actualiza los niveles mostrados para que el usuario seleccione.
	 */
	void mundoSeleccionadoCambiado();

	/**
	 * Conecta los botones de seleccion de mundo a la senial que actualiza
	 * los niveles mostrados.
	 */
	void conectarBotonesMundo();

	/**
	 * Agrega los widgets de este contenedor.
	 */
	void agregarComponentes();

	/**
	 * El usuario indico que desea volver al menu principal.
	 */
	void botonVolverClickeado();

	InterfazSelectora* interfazSelectora;
	SeleccionadorMultiple* selectorMundos;
	SeleccionadorMultiple* selectorNiveles;
	Gtk::Button* botonVolver;

	std::map<string, string> mundos;
	std::map<int, string> niveles;
};

#endif
