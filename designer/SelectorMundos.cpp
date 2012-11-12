#include "SelectorMundos.h"

SelectorMundos::SelectorMundos(std::map<std::string, std::string> nombreMundos) {
	set_policy(Gtk::POLICY_AUTOMATIC , Gtk::POLICY_ALWAYS);
	this->nombreMundos = nombreMundos;
	// Comienza la carga de los botones de los mundos
	mundos = new Gtk::RadioButton*[nombreMundos.size()];
	unsigned int contador = 0;
	std::map<std::string, std::string>::iterator iterador = nombreMundos.begin();
	while (iterador != nombreMundos.end()) {
		mundos[contador] = new Gtk::RadioButton(iterador->second);
		Gtk::RadioButton::Group grupo = mundos[0]->get_group();
		if (contador != 0)
			mundos[contador]->set_group(grupo);
		++iterador;
		++contador;
	}
	// Se agregan los mundos a la caja
	Gtk::VBox* caja = manage(new Gtk::VBox(false, 10));
	contador = 0;
	while (contador < nombreMundos.size()) {
		caja->pack_start(*mundos[contador]);
		++contador;
	}
	add(*caja);
}

SelectorMundos::~SelectorMundos() {
	unsigned int contador = 0;
	while (contador < nombreMundos.size()) {
		delete mundos[contador];
		++contador;
	}
	delete [] mundos;
}

std::string SelectorMundos::getNombreMundoSeleccionado() {
	int contadorBotones = 0;
	while (mundos[contadorBotones]->get_active() == false)
		++contadorBotones;
	std::map<std::string, std::string>::iterator iterador = nombreMundos.begin();
	while (iterador != nombreMundos.end()) {
		if (iterador->second.compare(mundos[contadorBotones]->get_label()) == 0)
			return iterador->first;
		++iterador;
	}
	return std::string("");
}

