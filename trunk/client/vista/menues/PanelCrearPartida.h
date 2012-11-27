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

// Constantes del layout y tamanio del selector de mundos
#define X_SELECTOR_MUNDOS_PARTIDAS 75
#define Y_SELECTOR_MUNDOS_PARTIDAS 100
#define ANCHO_SELECTOR_MUNDOS_PARTIDAS 275
#define ALTO_SELECTOR_MUNDOS_PARTIDAS 250
// Constantes de layout y tamanio del boton crear
#define X_BOTON_CREACION_PARTIDA 425
#define Y_BOTON_CREACION_PARTIDA 300
#define ANCHO_BOTON_CREACION_PARTIDA 100
#define ALTO_BOTON_CREACION_PARTIDA 50
// Constantes de layout y tamanio del selector de nombre
#define X_NOMBRE_PARTIDA 75
#define Y_NOMBRE_PARTIDA 420
#define ANCHO_NOMBRE_PARTIDA 275
#define ALTO_NOMBRE_PARTIDA 30
// Constantes de layout del boton crear
#define X_BOTON_VOLVER_CREAR_PARTIDA 25
#define Y_BOTON_VOLVER_CREAR_PARTIDA 550
// Constantes de layout y tamanio de las etiquetas
#define X_ETIQUETA_MUNDOS_PARTIDAS 75
#define Y_ETIQUETA_MUNDOS_PARTIDAS 50
#define X_ETIQUETA_NOMBRE_PARTIDA 75
#define Y_ETIQUETA_NOMBRE_PARTIDA 370

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
			InterfazSelectora* interfaz);

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
	 * El usuario indico que desea crear una partida.
	 */
	void botonCrearClickeado();

	/**
	 * El usuario indico que desea volver al menu multijugador.
	 */
	void botonVolverClickeado();

	/**
	 * Inicializa los componentes de este contenedor.
	 */
	void inicializarComponentes();

	InterfazSelectora* interfaz;
	SeleccionadorMultiple* selectorMundos;
	
	Gtk::Button* botonVolver;
	Gtk::Entry* nombre;

	std::map<string, string> mundos;
};

#endif
