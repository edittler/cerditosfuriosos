#ifndef _PANEL_IMAGEN_FONDO_H_
#define _PANEL_IMAGEN_FONDO_H_

#include <gtkmm/fixed.h>
#include <gtkmm/image.h>

#include <string>

using std::string;

/**
 * Un widget heredero de Fixed que tiene ademas un constructor que recibe la
 * ruta de un archivo con una imagen y la coloca de fondo en el mismo.
 */
class PanelImagenFondo : public Gtk::Fixed {
	public:
	
		/**
		 * Constructor.
		 * @param ruta ruta de la imagen que colocaremos de fondo
		 */
		PanelImagenFondo(int ancho, int alto, string ruta);
		
		/**
		 * Destructor.
		 */
		virtual ~PanelImagenFondo();
};

#endif
