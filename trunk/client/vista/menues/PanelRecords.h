#ifndef _PANEL_RECORDS_H_
#define _PANEL_RECORDS_H_

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/table.h>
#include <gtkmm/label.h>

#include <cstdlib>
#include <sstream>

#include <list>

#include "PanelImagenFondo.h"
#include "InterfazSelectora.h"

using std::list;
using std::pair;

// Constantes de tamanio layout de la ventana de records
#define X_VENTANA_RECORDS 100
#define Y_VENTANA_RECORDS 100
#define ANCHO_VENTANA_RECORDS 400
#define ALTO_VENTANA_RECORDS 400
// Constantes de layout del boton volver
#define X_BOTON_VOLVER_RECORDS 25
#define Y_BOTON_VOLVER_RECORDS 550

/**
 * Muestra una lista con los mejores puntajes en una ventaja desplazable.
 */
class PanelRecords : public PanelImagenFondo {
	public:
	
		/**
		 * Constructor.
		 */
		PanelRecords(int ancho, int alto, string ruta,
												InterfazSelectora* interfaz);
												
		/**
		 * Destructor.
		 */
		~PanelRecords();
		
	private:
	
		/**
		 * El usuario indico que desea volver al menu multijugador.
		 */
		void botonVolverClickeado();
		
		/**
		 * Carga los records en una lista, ordenados de mayor a menor.
		 */
		void cargarRecords();
		
		/**
		 * Agrega la ventana con los records al contenedor.
		 */
		void agregarComponentes();
		
		/**
		 * Carga los records en la ventana desplazable.
		 */
		void cargarVentana();
	
		InterfazSelectora* interfaz;	
		Gtk::ScrolledWindow* ventana;
		Gtk::Button* botonVolver;
	
		list< pair<string, int> > records;
};

#endif
