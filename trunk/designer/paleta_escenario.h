#ifndef _PALETA_ESCENARIO_H_
#define _PALETA_ESCENARIO_H_
#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>


// Ruta de las imagenes que se colocaran en los botones
#define RUTA_ITEM_CERDO "itemCerdo.png"
#define RUTA_ITEM_HUEVOS "itemHuevos.png"
#define RUTA_ITEM_CAJA_MADERA "itemCajaMadera.png"
#define RUTA_ITEM_CAJA_METAL "itemCajaMetal.png"

class PaletaEscenario : public Gtk::Frame {
	private:
	
		// Grupos de items que se veran en la paleta
		Gtk::Frame itemsJugador, itemsVarios;
		
		// Cajas donde se guardaran los items dentro de cada grupo
		Gtk::VBox cajaItemsJugador, cajaItemsVarios;
		
		// Caja donde se guardaran los grupos
		Gtk::VBox cajaGrupos;
		
		/**
		 * Agrega los items a los grupos, y estos a la paleta.
		 */
		void agregarItems();
		
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
	
	public:
	
		// Items contenidos en los grupos
		Gtk::Button itemCerdo, itemHuevos, itemCajaMadera, itemCajaMetal;
	
		/**
		 * Constructor.
		 */
		PaletaEscenario();
		
		/**
		 * Destructor.
		 */
		virtual ~PaletaEscenario();
		
};

#endif
