#ifndef VENTANACLIENTE_H_
#define VENTANACLIENTE_H_

#include <gtkmm.h>

class VentanaCliente: public Gtk::Window {
public:
	VentanaCliente();
	virtual ~VentanaCliente();

	void agregarContenedor(Gtk::Container* conteiner);

private:
	Gtk::Container* contenedor;
};

#endif /* VENTANACLIENTE_H_ */
