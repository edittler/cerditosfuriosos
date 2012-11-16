#ifndef _PALETA_ENTRADA_PAJAROS_H_
#define _PALETA_ENTRADA_PAJAROS_H_

#include "ConstantesDiseniador.h"

#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/spinbutton.h>

/**
 * Proporciona un panel en el cual se pueden seleccionar las caracteristicas de
 * la entrada de los pajaros enemigos.
 */
class EntradaPajaros : public Gtk::Frame {
	public:
	
		/**
		 * Constructor.
		 * @param anchoEscenario ancho del escenario en pixeles
		 * @param altoEscenario ancho del escenario en pixeles
		 */
		EntradaPajaros(int anchoEscenario, int altoEscenario);
		
		/**
		 * Destructor.
		 */
		virtual ~EntradaPajaros();
		
		/**
		 * @return true si la linea de entrada para los pajaros es valida y
		 * false en el caso contrario
		 */
		bool lineaEntradaValida();
		
		/**
		 * @return true si los porcentajes de aparicion de los pajaros suma 100
		 * y false en el caso contrario
		 */
		bool porcentajesPajarosValidos();
		
		/**
		 * @return coordenada x inicial de la linea de entrada de pajaros
		 */
		float getXInicioLineaEntrada();
		
		/**
		 * @return coordenada y inicial de la linea de entrada de pajaros
		 */
		float getYInicioLineaEntrada();
		
		/**
		 * @return coordenada x final de la linea de entrada de pajaros
		 */
		float getXFinalLineaEntrada();
		
		/**
		 * @return coordenada y final de la linea de entrada de pajaros
		 */
		float getYFinalLineaEntrada();
		
		/**
		 * @return tiempo de generacion de los pajaros
		 */
		int getTiempoGeneracion();
		
		/**
		 * @return probabilidad de generacion de los pajaros
		 */
		int getProbabilidadGeneracion();
		
		/**
		 * @return probabilidad del pajaro rojo
		 */
		int getProbabilidadPajaroRojo();
		
		/**
		 * @return probabilidad del pajaro verde
		 */
		int getProbabilidadPajaroVerde();
		
		/**
		 * @return probabilidad del pajaro azul
		 */
		int getProbabilidadPajaroAzul();
		
	private:
	
		Gtk::SpinButton* xInicial;
		Gtk::SpinButton* yInicial;
		
		Gtk::SpinButton* xFinal;
		Gtk::SpinButton* yFinal;
		
		Gtk::SpinButton* tiempoGeneracion;
		
		Gtk::SpinButton* probabilidadGeneracion;
		
		Gtk::SpinButton* probabilidadRojo;
		Gtk::SpinButton* probabilidadVerde;
		Gtk::SpinButton* probabilidadAzul;
};

#endif
