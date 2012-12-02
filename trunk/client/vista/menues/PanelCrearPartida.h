#ifndef _PANEL_CREAR_PARTIDA_H_
#define _PANEL_CREAR_PARTIDA_H_

// C++ Library Includes.
#include <map>
#include <string>

// GTK+ Library Includes.
#include <gtkmm/label.h>
#include <gtkmm/entry.h>

// Client Project Includes.
#include "PanelImagenFondo.h"
#include "SeleccionadorMultiple.h"
#include "InterfazSelectora.h"

/**
 * Muestra al usuario una lista de los mundos existentes para que cree una
 * partida que transcurra en uno de ellos, permitiendole elegir un nombre para
 * la misma.
 * 
 * Antes de mostrarselo debe enviarsele el mensaje cargarMundos con el string
 * correspondiente, dado que si no no se vera nada.
 */
class PanelCrearPartida : public PanelImagenFondo {
public:
	/**
	 * Constructor.
	 */
	PanelCrearPartida(int ancho, int alto, string ruta,
			InterfazSelectora& interfaz);

	/**
	 * Destructor.
	 */
	virtual ~PanelCrearPartida();

	/**
	 * Carga los mundos existentes en una lista para poder mostrarlos.
	 */
	void cargarMundos(std::string nombreMundos);

	std::string getMundoElegido();

	std::string getNombreElegido() const;
	
	Gtk::Button* botonCrear;

private:
	/**
	 * El usuario indico que desea volver al menu multijugador.
	 */
	void botonVolverClickeado();

	InterfazSelectora& interfaz;
	SeleccionadorMultiple* selectorMundos;
	
	Gtk::Button* botonVolver;
	Gtk::Entry* nombre;

	std::map<string, string> mundos;
};

#endif
