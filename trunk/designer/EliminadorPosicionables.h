#ifndef _ELIMINADOR_POSICIONABLES_H_
#define _ELIMINADOR_POSICIONABLES_H_

// GTK+ Library Includes.
#include <gtkmm/label.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>

// Designer Project Includes.
#include "Lienzo.h"

/**
 * Proporciona un widget hacia donde se pueden arrastrar los posicionables para
 * eliminarlos una vez colocados.
 */
class EliminadorPosicionables : public Gtk::EventBox {
public:

	/**
	 * Constructor.
	 * @param lienzo puntero hacia la instancia de la clase Lienzo cuyos
	 * posicionables eliminara este objeto
	 */
	explicit EliminadorPosicionables(Lienzo* lienzo);

	/**
	 * Destructor.
	 */
	virtual ~EliminadorPosicionables();

protected:
	/**
	 * Recibe informacion de un drag and drop y obra en funcion de esta.
	 */
	void recibirInformacion(const Glib::RefPtr<Gdk::DragContext>& context,
								int x,
								int y,
								const Gtk::SelectionData& selection_data,
								guint info,
								guint time);

private:
		Lienzo* lienzo;
		Gtk::HBox caja;
		std::list<Gtk::TargetEntry> listaObjetivos;
};

#endif
