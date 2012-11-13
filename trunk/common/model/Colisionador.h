#ifndef COLISIONADOR_H_
#define COLISIONADOR_H_

// Box2D Library Includes.
#include "Box2D/Dynamics/b2WorldCallbacks.h"

// Project Includes.
#include "CuerpoAbstracto.h"

class Colisionador: public b2ContactListener {
public:
	Colisionador();
	virtual ~Colisionador();

	/* Se le llama cuando dos fixtures se comienzan a tocar.
	 */
	void BeginContact(b2Contact* contact);

	/* Se le llama cuando dos fixtures se dejan de tocar.
	 */
	void EndContact(b2Contact* contact);

	/* Se llama después de que un contact se actualiza. Esto permite inspeccionar
	 * un contacto antes de reslver. Si usted tiene cuidado, puede modificar el
	 * colector de contacto (por ejemplo, deshabilitar contacto).
	 * Una copia del colector antiguo se proporciona para que pueda detectar los
	 * cambios.
	 * Nota: esto se llama sólo para cuerpos despiertos.
	 * Nota: esto se llama incluso cuando el número de puntos de contacto es cero.
	 * Nota: esto no es llamado por los sensores.
	 * Nota: si se establece el número de puntos de contacto a cero, no se
	 * obtendrá una llamada a EndContact. Sin embargo, se puede obtener una
	 * llamada a BeginContact el siguiente paso.
	 */
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	/* Esto permite inspeccionar un contact después de que el solver ha terminado.
	 * Es útil para la inspección de impulsos.
	 * Nota: el colector de contacto no incluye el tiempo de los impulsos de
	 * impacto, que puede ser arbitrariamente grande si la subetapa es pequeña.
	 * Por lo tanto el impulso se proporciona explícitamente en una estructura
	 * de datos separada.
	 * Nota: esto sólo se llama para los contactos que estén en contacto,
	 * sólido y despierto.
	 */
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

private:
	void chocarPajaroConSuperficie(CuerpoAbstracto* cuerpoA,
			CuerpoAbstracto* cuerpoB);
	void chocarPajaroConFruta(CuerpoAbstracto* cuerpoA,
			CuerpoAbstracto* cuerpoB);
	void chocarPajaroConCerdito(CuerpoAbstracto* cuerpoA,
			CuerpoAbstracto* cuerpoB);
	void chocarPajaroConMonticulo(CuerpoAbstracto* cuerpoA,
			CuerpoAbstracto* cuerpoB);

	void chocarDisparoConSuelo(CuerpoAbstracto* cuerpoA,
			CuerpoAbstracto* cuerpoB);
	void chocarDisparoConSuperficie(CuerpoAbstracto* cuerpoA,
			CuerpoAbstracto* cuerpoB);
	void chocarDisparoConFruta(CuerpoAbstracto* cuerpoA,
			CuerpoAbstracto* cuerpoB);
	void chocarDisparoConCerdito(CuerpoAbstracto* cuerpoA,
			CuerpoAbstracto* cuerpoB);
	void chocarDisparoConMonticulo(CuerpoAbstracto* cuerpoA,
			CuerpoAbstracto* cuerpoB);
	void chocarDisparoConPajaro(CuerpoAbstracto* cuerpoA,
			CuerpoAbstracto* cuerpoB);
};

#endif /* COLISIONADOR_H_ */
