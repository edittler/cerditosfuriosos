#ifndef CUERPOABSTRACTO_H_
#define CUERPOABSTRACTO_H_

// Hierarchy Include.
#include "CuerpoObservable.h"

// Box2D Library Includes.
#include "Box2D/Box2D.h"

// Project Includes.
#include "Velocidad2D.h"

/* @class CuerpoAbstracto
 * Interfaz que define un cuerpo con una vida. Implementa el CuerpoObservable,
 * dado que los cuerpos que hereden de CuerpoAbstracto pueden ser vistos por
 * otros objetos mediante el patrón observador, por ejemplo, para la vista.
 */
class CuerpoAbstracto: public CuerpoObservable {
public:
	/* Constructor antiguo sin parametros.
	 */
	CuerpoAbstracto();

	/* @brief Constructor que inicializa los atributos.
	 * @param cuerpo de Box2D.
	 * @param vida que va a tener el cuerpo.
	 */
	CuerpoAbstracto(b2Body* cuerpo, float vida);

	/* Destructor
	 */
	virtual ~CuerpoAbstracto();

	/* @brief Retorna el estado del cuerpo
	 * @return true si el cuerpo esta vivo, false si esta muerto
	 */
	bool estaVivo() const;

	/* @brief Resta vida segun @param.
	 * @param Cantidad a restar.
	 */
	void daniar(float danio);

	/* @brief Cambia el estado del objeto a "muerto".
	 */
	void matar();

	/* @brief Registra un observador.
	 * @param Observador a registrar.
	 */
	void registrarObservador(ObservadorCuerpo* observador);

	/* @brief Elimina el observador. En caso de que no exista el observador
	 * dado, no realiza nada.
	 */
	void eliminarObservador(ObservadorCuerpo* observador);

	/* @brief Notifica la posicion del cuerpo al observador.
	 */
	void notificarPosicionAObservador();

	Punto2D getPosicion() const;

	Velocidad2D getVelocidad() const;

	/*
	 * @brief devuelve b2Body asociado al objeto.
	 * Usado para correcta eliminacion del mundo fisico (Box2D)
	 */
	b2Body* getBody();

	void eliminarBody();

	void printPosition() const; // TODO PROVISORIO, BORRAR

protected:

	// Cuerpo de Box2D que se encapsula.
	b2Body* cuerpo;

	// Vida del cuerpo.
	float vida;

	// Observador del cuerpo.
	ObservadorCuerpo* observador;
};

#endif /* CUERPOABSTRACTO_H_ */
