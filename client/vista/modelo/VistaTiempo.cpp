// Project Include
#include "VistaTiempo.h"
#include "ConstantesVistaModelo.h"
#include "CFTools.h"

// Forward declaration
#include "VistaEscenario.h"


VistaTiempo::VistaTiempo(VistaEscenario* escenario) {
	this->escenario = escenario;
	this->label.set_text("00:00");
	Pango::AttrList list;
	Pango::Attribute at = Pango::Attribute::create_attr_scale(ESCALA_TEXTO);
	list.insert(at);
	at = Pango::Attribute::create_attr_foreground(COLOR_TEXTO, COLOR_TEXTO, COLOR_TEXTO);
	list.insert(at);
	this->label.set_attributes(list);
	escenario->put(this->label, POSICION_TIEMPO_X, POSICION_TIEMPO_Y);
}

VistaTiempo::~VistaTiempo() { }

void VistaTiempo::setTiempo(unsigned int miliseg) {
	std::string tiempo;
	unsigned int min = round(miliseg / 1000) / 60;
	unsigned int seg = round((miliseg / 1000) % 60);

	if ((min / 10) < 1)
		tiempo.append("0");
	tiempo.append(cft::intToString(min));
	tiempo.append(":");

	if ((seg / 10) < 1) {
		Pango::AttrList list = this->label.get_attributes();
		Pango::Attribute at = Pango::Attribute::create_attr_foreground(COLOR_TEXTO, 0, 0);
		list.change(at);
		this->label.set_attributes(list);
		tiempo.append("0");
	}
	tiempo.append(cft::intToString(seg));

	label.set_text(tiempo);
}
