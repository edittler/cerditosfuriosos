#ifndef _LIENZO_H_
#define _LIENZO_H_
#include <string>
#include <gtkmm/fixed.h>
#include <gtkmm/eventbox.h>
#include <list>
#include "InformableSeleccion.h"
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
		Lienzo(int ancho,
				int alto,
				int cantidadJugadores,
				string rutaFondo,
				InformableSeleccion* informable);
	
		/**
		 * @param rutaNivel cargaremos los objetos pertenecientes a un nivel que
		 * se quiere editar
		 */
		void cargarNivel(string rutaNivel);
		
		/**
		 * @param rutaNivel guardaremos los objetos pertenecientes al nivel ya
		 * editado
		 */
		void guardarNivel(string rutaNivel);
		
	
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
		
		InformableSeleccion* informable;
	
		Gtk::Image* imagenFondo;
		list<Gtk::TargetEntry> listaObjetivos;
		
		list<ImagenCajaMadera*> cajasMadera;
		list<ImagenCajaMetal*> cajasMetal;
		list<ImagenCajaVidrio*> cajasVidrio;
		list<ImagenCerdo*> cerdos;
		ImagenHuevos* monticulo;
		list<ImagenBanana*> bananas;
		list<ImagenCereza*> cerezas;
		list<ImagenManzana*> manzanas;
		list<ImagenCatapulta*> catapultas;
		
		list<ImagenPosicionable*> posicionables;
		
		/**
		 * Le copia el fondo a una imagen posicionable.
		 * @param x abscisa a partir de la cual queremos copiar el fondo
		 * @param y ordenada a partir de la cual queremos copiar el fondo
		 * @param imagen puntero a la imagen posicionable a la cual le
		 * copiaremos el fondo
		 */
		void copiarFondo(int x, int y, ImagenPosicionable* imagen);
		
		/**
		 * Se le pasa la ruta de una imagen y la escala para ponerla de fondo.
		 */
		void agregarFondo(string rutaImagen);
		
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
		void agregarMonticulo(int x, int y);
	
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
		
		/**
		 * Los siguientes metodos estan sobrecargados para los casos en los que
		 * se carga un nivel desde un archivo.
		 */
		void agregarCerdo(float x, float y);
		void agregarMonticulo(float x, float y);
		void agregarCatapulta(float x, float y);
		void agregarCajaMadera(float x, float y);
		void agregarCajaMetal(float x, float y);
		void agregarCajaVidrio(float x, float y);
		void agregarBanana(float x, float y);
		void agregarCereza(float x, float y);
		void agregarManzana(float x, float y);
};

#endif
