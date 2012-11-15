#include "SelectorNiveles.h"

SelectorNiveles::SelectorNiveles(std::map<int, std::string> idNiveles) {
	this->idNiveles = idNiveles;
	set_policy(Gtk::POLICY_AUTOMATIC , Gtk::POLICY_ALWAYS);
	Gtk::VBox* caja = manage(new Gtk::VBox(false, 10));
	// A partir de aqui se comienzan a cargar los niveles.
	niveles = new Gtk::RadioButton*[idNiveles.size()];
	unsigned int contador = 0;
	std::map<int, std::string>::iterator iterador = idNiveles.begin();
	while (iterador != idNiveles.end()) {
		std::string numero;
		numero += ((char)(iterador->first+'0'));
		niveles[contador] = new Gtk::RadioButton(numero);
		Gtk::RadioButton::Group grupo = niveles[0]->get_group();
		if (contador != 0)
			niveles[contador]->set_group(grupo);
		++iterador;
		++contador;
	}
	// Se agregan los niveles a la caja
	contador = 0;
	while (contador < idNiveles.size()) {
		caja->pack_start(*niveles[contador]);
		++contador;
	}
	add(*caja);
}

SelectorNiveles::~SelectorNiveles() {
	unsigned contador = 0;
	while (contador < idNiveles.size()) {
		delete niveles[contador];
		++contador;
	}
	delete [] niveles;
}

std::string SelectorNiveles::getRutaNivelSeleccionado() {
	int contadorBotones = 0;
	while (niveles[contadorBotones]->get_active() == false)
		++contadorBotones;
	int numero = (niveles[contadorBotones]->get_label()[0] - '0');
	std::map<int, std::string>::iterator iterador = 
						idNiveles.find(numero);
	return iterador->second;
}
