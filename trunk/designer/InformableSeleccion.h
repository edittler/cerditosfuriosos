#ifndef _INFORMABLE_SELECCION_H_
#define _INFORMABLE_SELECCION_H_

#include <string>

/**
 * Interfaz pensada para que los distintos paneles del diseñador le informen a 
 * su ventana cuando el usuario ingrese una informacion de importancia.
 */
class InformableSeleccion {
	public:
	
		/**
		 * El usuario ha informado que desea editar un mundo.
		 * @param rutaMundo ruta del archivo del mundo seleccionado
		 */
		virtual void editarMundo(std::string rutaMundo) = 0;
		
		/**
		 * El usuario ha seleccionado un nombre invalido.
		 */
		virtual void nombreSeleccionadoInvalido() = 0;
		
		/**
		 * El usuario ha informado que desea crear un nivel.
		 */
		virtual void crearNivel() = 0;
		
		/**
		 * @return ruta de una imagen seleccionada por el usuario
		 */
		virtual std::string seleccionarImagen() = 0;
		
		virtual ~InformableSeleccion() {};
};

#endif
