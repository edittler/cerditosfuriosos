#ifndef _SELECCIONADOR_MULTIPLE_H_
#define _SELECCIONADOR_MULTIPLE_H_

#include <gtkmm/paned.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>

#include <cstdlib>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::stringstream;

/**
 * Widget de proposito general.
 * 
 * Muestra una ventana desplazable con varios botones de radio.
 * 
 * Para crearlo se le pasa una std::map, donde el primer miembro del par puede
 * ser un std::string o un int, y el segundo es un std::string.
 * 
 * Se mostrara un boton de radio que cuya etiqueta sea el primer miembro de cada
 * par.
 * 
 * El metodo getOpcionSeleccionada() devuelve un std::string que es igual al
 * segundo miembro del par cuyo primer miembro se corresponde con el boton de
 * radio activo.
 * 
 * De esta manera uno puede asociar los nombres de los mundos o el id de los
 * niveles con las rutas de los archivos correspondientes.
 */
class SeleccionadorMultiple : public Gtk::ScrolledWindow {
	public:
	
		/**
		 * Constructor.
		 * @param mapa mapa de pares de string donde el primer miembro de cada
		 * una nombrara a uno de los botones de radio seleccionables y lo
		 * asociara con el segundo
		 */
		SeleccionadorMultiple(int ancho,
								int alto,
								std::map<string, string> mapa);
		
		/**
		 * Constructor.
		 * @param mapa mapa de pares de enteros donde el primer miembro de
		 * cada una nombrara a uno de los botones de radio seleccionables y
		 * lo asociara con el segundo
		 */
		SeleccionadorMultiple(int ancho,
								int alto,
								std::map<int, string> mapa);
		
		/**
		 * Destructor.
		 */
		virtual ~SeleccionadorMultiple();
		
		/**
		 * @return string que es igual al segundo miembro del par cuyo primer
		 * miembro se corresponde con el boton de radio activo.
		 */
		string getOpcionSeleccionada();
		
		/**
		 * Los siguientes metodos estan pensados para cuando se desean cambiar
		 * los botones que contiene este objeto.
		 */
		void actualizarBotones(std::map<string, string> mapa);
		void actualizarBotones(std::map<int, string> mapa);
		
		Gtk::RadioButton** botones;
		int cantidadBotones;
	
	private:
	
		/**
		 * Recorre el mapa recibido en el creador e instancia los botones de
		 * radio.
		 */
		void crearBotones(std::map<string, string> mapa);
		void crearBotones(std::map<int, string> mapa);
		
		/**
		 * Agrega los botones a la ventana desplazable.
		 */
		void agregarBotones();
		
		std::map<string, string> mapa;
};

#endif
