#ifndef _PANEL_ESCENARIO_H_
#define _PANEL_ESCENARIO_H_

// GTK+ Library Includes.
#include <gtkmm/paned.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>

// Designer Project Includes.
#include "PaletaEscenario.h"
#include "EliminadorPosicionables.h"
#include "Lienzo.h"
#include "EntradaPajaros.h"
#include "InformableSeleccion.h"

/**
 * Muestra el panel que permite editar un escenario.
 */
class PanelEscenario : public Gtk::Paned {
public:

	/**
	 * Constructor.
	 */
	PanelEscenario(std::string rutaNivel,
					InformableSeleccion* informable,
					int cantidadJugadores,
					bool nivelNuevo);

	/**
	 * Destructor.
	 */
	~PanelEscenario();

	protected:

	/**
	 * Metodo invocado cuando se clickea al boton que guarda el nivel.
	 * Previamente a guardar exije al usario que deje al escenario en un
	 * estado valido si este no es asi.
	 */
	void botonGuardarClickeado();

private:
	
	/**
	 * El usuario informa que desea volver al panel de seleccion de mundos.
	 */
	void volverAPanelMundos();

	/**
	 * Guardar las caracteristicas del Escenario.
	 */
	void guardarCaracteristicasEscenario() const;

	/**
	 * Carga las caracteristicas del nivel en atributos propios.
	 */
	void cargarCaracteristicasNivel();

	/* Limpia el nodo del nivel, borrando los nodos Escenario y Lineas de
	 * de pajaros.
	 */
	void limpiarNodoNivel(XMLNode* nodo) const;

	PaletaEscenario* paletaEscenario;
	EliminadorPosicionables* eliminador;
	Lienzo* lienzo;
	EntradaPajaros* entrada;
	Gtk::Button* botonGuardar;
	Gtk::Button* botonVolver;

	InformableSeleccion* informable;

	std::string rutaNivel;
	float anchoFlotante;
	float altoFlotante;
	std::string rutaFondo;
	int cantidadJugadores;
};

#endif
