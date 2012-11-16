#ifndef _PALETA_ESCENARIO_H_
#define _PALETA_ESCENARIO_H_

#include "ConstantesDiseniador.h"

#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/image.h>

class PaletaEscenario : public Gtk::Frame {
	public:
			
		/**
		 * Constructor.
		 */
		PaletaEscenario();
		
		/**
		 * Destructor.
		 */
		virtual ~PaletaEscenario();
	
	protected:
		
		void boton_cerdo_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
		void boton_catapulta_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
		void boton_huevos_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
		void boton_caja_madera_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
		void boton_caja_metal_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
		void boton_caja_vidrio_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
		void boton_banana_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
		void boton_cereza_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
		void boton_manzana_arrastrado(
								const Glib::RefPtr<Gdk::DragContext>& context,
								Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
	private:
	
		std::list<Gtk::TargetEntry> listaObjetivos;

		// Items contenidos en los grupos
		Gtk::Button itemCajaMadera, itemCajaMetal, itemCajaVidrio, itemCerdo,
					itemHuevos, itemBanana, itemCereza, itemManzana,
					itemCatapulta;
		
		// Grupos de items que se veran en la paleta
		Gtk::Frame itemsJugador, itemsCajas, itemsFrutas;
		
		// Cajas donde se guardaran los items dentro de cada grupo
		Gtk::VBox* cajaItemsJugador;
		Gtk::VBox* cajaItemsCajas;
		Gtk::VBox* cajaItemsFrutas;
		
		// Caja donde se guardaran los grupos
		Gtk::VBox* cajaGrupos;
		
		/**
		 * Agrega los items a los grupos, y estos a la paleta.
		 */
		void agregarItems();
};

#endif
