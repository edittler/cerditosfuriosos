#ifndef _PANEL_UNIRSE_PARTIDA_H_
#define _PANEL_UNIRSE_PARTIDA_H_

#include <gtkmm/label.h>

#include <map>

#include "PanelImagenFondo.h"
#include "SeleccionadorMultiple.h"
#include "InterfazSelectora.h"

// Constantes del layout y tamanio del selector
#define X_SELECTOR_PARTIDAS 75
#define Y_SELECTOR_PARTIDAS 200
#define ANCHO_SELECTOR_PARTIDAS 275
#define ALTO_SELECTOR_PARTIDAS 250
// Constantes de layout y tamanio del boton seleccionar
#define X_BOTON_SELECCIONAR_PARTIDA 425
#define Y_BOTON_SELECCIONAR_PARTIDA 300
#define ANCHO_BOTON_SELECCIONAR_PARTIDA 100
#define ALTO_BOTON_SELECCIONAR_PARTIDA 50
// Constantes de layout del boton volver
#define X_BOTON_VOLVER_PARTIDA 25
#define Y_BOTON_VOLVER_PARTIDA 550
// Constantes de layout y tamanio de las etiquetas
#define X_ETIQUETA_PARTIDAS 75
#define Y_ETIQUETA_PARTIDAS 150

/**
 * Muestra al usuario una lista de las partidas existentes para jugar en modo
 * multijugador.
 */
class PanelUnirsePartida : public PanelImagenFondo {
	public:
	
		/**
		 * Constructor.
		 */
		PanelUnirsePartida(int ancho,
						int alto,
						string ruta,
						InterfazSelectora* interfaz);
						
		/**
		 * Destructor.
		 */
		virtual ~PanelUnirsePartida();
	
	private:
	
		/**
		 * El usuario indico que desea volver al menu multijugador.
		 */
		void botonSeleccionarClickeado();
		
		/**
		 * El usuario indico que desea volver al menu multijugador.
		 */
		void botonVolverClickeado();
		
		/**
		 * Carga las partidas existentes en una lista para poder mostrarlas.
		 */
		void cargarPartidas();
		
		/**
		 * Agrega los componentes a este contenedor.
		 */
		void agregarComponentes();
	
		InterfazSelectora* interfaz;
		SeleccionadorMultiple* selectorPartidas;
		Gtk::Button* botonSeleccionar;
		Gtk::Button* botonVolver;
	
		std::map<string, string> partidas;
};

#endif
