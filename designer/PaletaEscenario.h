#ifndef _PALETA_ESCENARIO_H_
#define _PALETA_ESCENARIO_H_
#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/eventbox.h>

// Ruta de las imagenes que se colocaran en los botones
#define RUTA_ITEM_CAJA_MADERA "imagenes/itemCajaMadera.png"
#define RUTA_ITEM_CAJA_METAL "imagenes/itemCajaMetal.png"
#define RUTA_ITEM_CAJA_VIDRIO "imagenes/itemCajaVidrio.png"
#define RUTA_ITEM_CERDO "imagenes/itemCerdo.png"
#define RUTA_ITEM_HUEVOS "imagenes/itemHuevos.png"

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
								
	private:
	
		std::list<Gtk::TargetEntry> listaObjetivos;

		// Items contenidos en los grupos
		Gtk::Button itemCajaMadera, itemCajaMetal, itemCajaVidrio, itemCerdo,
					itemHuevos;
		
		// Grupos de items que se veran en la paleta
		Gtk::Frame itemsJugador, itemsVarios;
		
		// Cajas donde se guardaran los items dentro de cada grupo
		Gtk::VBox* cajaItemsJugador;
		Gtk::VBox* cajaItemsVarios;
		
		// Caja donde se guardaran los grupos
		Gtk::VBox* cajaGrupos;
		
		/**
		 * Agrega los items a los grupos, y estos a la paleta.
		 */
		void agregarItems();
};

#endif
