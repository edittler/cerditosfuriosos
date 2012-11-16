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
		 * El usuario ha dejado el campo de seleccion un nombre sin texto.
		 */
		virtual void nombreSeleccionadoVacio() = 0;
		
		/**
		 * El usuario ha optado por un nombre ya existente.
		 */
		virtual void nombreSeleccionadoYaExistente() = 0;
		
		/**
		 * El usuario ha informado que desea editar un nivel.
		 * @param rutaNivel ruta del archivo del nivel
		 */
		virtual void editarNivel(std::string rutaNivel) = 0;
		
		/**
		 * @return ruta de una imagen seleccionada por el usuario
		 */
		virtual std::string seleccionarImagen() = 0;
		
		/**
		 * Informa que el usuario quiere crear un escenario pero no ha elegido
		 * ninguna imagen para su fondo.
		 */
		virtual void imagenNoSeleccionada() = 0;

		/**
		 * Muestra un dialogo con el mensaje pasado por parametro
		 */
		virtual void mostrarDialogo(std::string mensaje) = 0;
		
		virtual ~InformableSeleccion() {};
};

#endif
