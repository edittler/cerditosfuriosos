#ifndef _PANEL_NIVEL_H_
#define _PANEL_NIVEL_H_

// GTK++ Library Includes.
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>

// Common Project Includes.
#include "XMLTypes.h"

// Designer Project Includes.
#include "SelectorNiveles.h"
#include "CreadorNivel.h"
#include "InformableSeleccion.h"

class PanelNivel : public Gtk::Paned {
public:
	/**
	 * Constructor.
	 * @param rutaMundo ruta del archivo del mundo a quien le queremos
	 * agregar niveles o cuyos niveles queremos editar
	 * @param informable se le informara cuando el usuario seleccione
	 * ciertas informaciones de relevancia
	 */
	PanelNivel(std::string rutaMundo, InformableSeleccion* informable);

	/**
	 * Destructor.
	 */
	virtual ~PanelNivel();

	/**
	 * @return cantidad de jugadores que juegan este nivel
	 */
	int getCantidadJugadores() const;

protected:
	/**
	 * Metodo llamado cuando se clickea el boton de creacion de mundo.
	 */
	void botonCrearClickeado();

	/**
	 * Metodo llamado cuando se clickea el boton de edicion de mundo.
	 */
	void botonEditarClickeado();

private:
	/**
	 * Carga el nombre del mundo, la cantidad de jugadores que permite y
	 * los niveles que posee.
	 * @param rutaMundo ruta del archivo que contiene al mundo al cual
	 * pertenecen los niveles
	 */
	void cargarCaracteristicasMundo();
	
	/**
	 * Carga en un contenedor mapa las rutas de los niveles, para ser
	 * accedidas a partir de la id de los mismos.
	 * @param rutaMundo ruta del archivo que contiene al mundo al cual
	 * pertenecen los niveles
	 */
	void cargarNiveles(const XMLNode* nodoNiveles);

	/**
	 * Actualiza el archivo del mundo agregando el nivel recien creado y la ruta
	 * del archivo donde se almacenará.
	 * @param rutaNivel ruta del archivo de nivel.
	 */
	void actualizarArchivoMundo(const std::string rutaNivel) const;

	InformableSeleccion* informable;
	SelectorNiveles* selector;
	CreadorNivel* creador;
	Gtk::Button* botonEditar;
	Gtk::Button* botonCrear;

	std::map<int, std::string> idNiveles;
	std::string rutaMundo;

	std::string nombreMundo;
	int cantidadJugadores;
};

#endif
