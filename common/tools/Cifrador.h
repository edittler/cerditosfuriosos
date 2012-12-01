#ifndef CIFRADOR_H_
#define CIFRADOR_H_

#include <string>

#define CLAVE_DEFAULT 96

/**
 * Cifra y descifra mensajes.
 * Aplica un cifrado básico por sustitución.
 */
class Cifrador {
public:
	Cifrador();
	virtual ~Cifrador();

	void cifrar(std::string& msj, int clave = CLAVE_DEFAULT);

	void descifrar(std::string& msj, int clave = CLAVE_DEFAULT);
};

#endif /* CIFRADOR_H_ */
