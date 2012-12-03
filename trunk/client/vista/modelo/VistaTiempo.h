#ifndef VISTATIEMPO_H_
#define VISTATIEMPO_H_

// Gtk Includes
#include <gtkmm/label.h>

// Forward declaration
class VistaEscenario;

class VistaTiempo {
public:
	explicit VistaTiempo(VistaEscenario* escenario);
	virtual ~VistaTiempo();

	void setTiempo(unsigned int miliseg);

private:
	VistaEscenario* escenario;

	Gtk::Label label;
};

#endif /* VISTATIEMPO_H_ */
