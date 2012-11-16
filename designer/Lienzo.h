#ifndef _LIENZO_H_
#define _LIENZO_H_
#include <string>
#include <gtkmm/fixed.h>
#include <gtkmm/eventbox.h>
#include <list>
#include "ConstantesDiseniador.h"
#include "ImagenCajaMadera.h"
#include "ImagenCajaMetal.h"
#include "ImagenCajaVidrio.h"
#include "ImagenCerdo.h"
#include "ImagenHuevos.h"
#include "ImagenBanana.h"
#include "ImagenCereza.h"
#include "ImagenManzana.h"
#include "ImagenCatapulta.h"

using std::list;
using std::string;

/**
 * Las instancias de esta clase representan a un contenedor vacio, sobre el cual
 * podemos arrastrar los objetos que integran el escenario del juego.
 */
class Lienzo : public Gtk::Fixed {
	public:
	
		/**
		 * Constructor.
		 */
		Lienzo(int ancho, int alto, int cantidadJugadores);
	
		/**
		 * Destructor.
		 */
		virtual ~Lienzo();
		
		/**
		 * @param id identificador de la imagen contenida en este lienzo que se
		 * quiere eliminar
		 */
		void eliminarImagen(string id);
		
		/**
		 * @return true si la cantidad de jugadores agregados es la
		 * correspondiente al nivel y false en el caso contrario
		 */
		bool cantidadJugadoresValida();
		
		/**
		 * @return true si por cada cerdo hay una catapulta y un monticulo y
		 * false en el caso contrario
		 */
		bool objetosJugadoresCorrectos();
	
	protected:
	
		/**
		 * Recibe informacion de un drag and drop e instancia una imagen
		 * posicionable en funcion de esta.
		 */
		void recibirInformacion(
								const Glib::RefPtr<Gdk::DragContext>& context,
								int x,
								int y,
								const Gtk::SelectionData& selection_data,
								guint info,
								guint time);
								
	private:
	
		unsigned int cantidadJugadores;
		int ancho;
		int alto;
	
		list<Gtk::TargetEntry> listaObjetivos;
		
		list<ImagenCajaMadera*> cajasMadera;
		list<ImagenCajaMetal*> cajasMetal;
		list<ImagenCajaVidrio*> cajasVidrio;
		list<ImagenCerdo*> cerdos;
		list<ImagenHuevos*> huevos;
		list<ImagenBanana*> bananas;
		list<ImagenCereza*> cerezas;
		list<ImagenManzana*> manzanas;
		list<ImagenCatapulta*> catapultas;
		
		list<ImagenPosicionable*> posicionables;
		
		/**
		 * @param id identificador del posicionable contenido en este lienzo que
		 * se quiere eliminar
		 */
		void eliminarPosicionable(string id);
		
		/**
		 * Agrega un cerdo en la posicion indicada por los parametros
		 * @param x abscisa donde queremos agregar la imagen
		 * @param y ordenada donde queremos agregar la imagen
		 */
		void agregarCerdo(int x, int y);

		/**
		 * Agrega un monticulo en la posicion indicada por los parametros
		 * @param x abscisa donde queremos agregar la imagen
		 * @param y ordenada donde queremos agregar la imagen
		 */
		void agregarHuevos(int x, int y);
	
		/**
		 * Agrega una catapulta en la posicion indicada por los parametros
		 * @param x abscisa donde queremos agregar la imagen
		 * @param y ordenada donde queremos agregar la imagen
		 */
		void agregarCatapulta(int x, int y);
	
		/**
		 * Agrega una caja de madera en la posicion indicada por los parametros
		 * @param x abscisa donde queremos agregar la imagen
		 * @param y ordenada donde queremos agregar la imagen
		 */
		void agregarCajaMadera(int x, int y);
	
		/**
		 * Agrega una caja de metal en la posicion indicada por los parametros
		 * @param x abscisa donde queremos agregar la imagen
		 * @param y ordenada donde queremos agregar la imagen
		 */
		void agregarCajaMetal(int x, int y);
	
		/**
		 * Agrega una caja de vidrio en la posicion indicada por los parametros
		 * @param x abscisa donde queremos agregar la imagen
		 * @param y ordenada donde queremos agregar la imagen
		 */
		void agregarCajaVidrio(int x, int y);
	
		/**
		 * Agrega una banana en la posicion indicada por los parametros
		 * @param x abscisa donde queremos agregar la imagen
		 * @param y ordenada donde queremos agregar la imagen
		 */
		void agregarBanana(int x, int y);
	
		/**
		 * Agrega una cereza en la posicion indicada por los parametros
		 * @param x abscisa donde queremos agregar la imagen
		 * @param y ordenada donde queremos agregar la imagen
		 */
		void agregarCereza(int x, int y);
	
		/**
		 * Agrega una manzana en la posicion indicada por los parametros
		 * @param x abscisa donde queremos agregar la imagen
		 * @param y ordenada donde queremos agregar la imagen
		 */
		void agregarManzana(int x, int y);
		
		/**
		 * Mueve el objeto identificado por el primer parametro hacia el punto,
		 * siempre y cuando no vaya a ocupar la posicion de otro objeto ya
		 * agregado ni a salirse de los limites.
		 * @param x abscisa donde queremos agregar a la imagen
		 * @param y ordenada donde queremos agregar a la imagen
		 */
		void moverObjeto(string id, int x, int y);
		
		/**
		 * @param x abscisa de la esquina superior derecha del objeto a agregar
		 * @param x ordenada de la esquina superior derecha del objeto a agregar
		 * @param imagen objeto a agregar
		 * @return true si el objeto a agregar coincidira espacialmente con
		 * alguno ya agregado y false en el caso contrario
		 */
		bool coincidenciaOcupacional(int x, int y, ImagenPosicionable* imagen);
		
		/**
		 * @param x abscisa de la esquina superior derecha del objeto a agregar
		 * @param x ordenada de la esquina superior derecha del objeto a agregar
		 * @param imagen objeto a agregar
		 * @return true si el objeto a agregar esta espacialmente dentro del
		 * escenario y false en el caso contrario
		 */
		bool dentroDeEscenario(int x, int y, ImagenPosicionable* imagen);
};

#endif
