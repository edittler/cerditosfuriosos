#ifndef _PANEL_MULTIJUGADOR_H_
#define _PANEL_MULTIJUGADOR_H_

#include "PanelImagenFondo.h"
#include "InterfazSelectora.h"

#include <gtkmm/fixed.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>

// Constantes de layout
#define ANCHO_BOTONES_MULTIJUGADOR 150
#define ALTO_BOTONES_MULTIJUGADOR 50
#define X_BOTON_CREAR_PARTIDA 400
#define Y_BOTON_CREAR_PARTIDA 100
#define X_BOTON_UNIRSE_PARTIDA 400
#define Y_BOTON_UNIRSE_PARTIDA 200
#define X_BOTON_RECORDS 400
#define Y_BOTON_RECORDS 300
// Constantes de layout del boton volver
#define X_BOTON_VOLVER 25
#define Y_BOTON_VOLVER 550

/**
 * Muestra al usuario las opciones de crear una partida multijugador, unirse a
 * una ya existente, o de ver los records.
 */
class PanelMultijugador : public PanelImagenFondo {
public:

	/**
	 * Constructor.
	 */
	PanelMultijugador(int ancho, int alto, string ruta,
			InterfazSelectora* interfaz);

	virtual ~PanelMultijugador();

	Gtk::Button* botonCrearPartida;
	Gtk::Button* botonUnirsePartida;
	Gtk::Button* botonRecords;
	Gtk::Button* botonVolver;

protected:

	/**
	 * El usuario ha indicado que quiere crear una partida.
	 */
	void botonCrearPartidaClickeado();

	/**
	 * El usuario ha indicado que quiere unirse a una partida existente.
	 */
	void botonUnirsePartidaClickeado();

	/**
	 * El usuario ha indicado que quiere ver los records.
	 */
	void botonRecordsClickeado();

	/**
	 * El usuario ha indicado que quiere volver al menu inicial.
	 */
	void botonVolverClickeado();
	
private:

	/**
	 * Agrega los botones al panel
	 */
	void agregarBotones();

	InterfazSelectora* interfaz;
};

#endif
