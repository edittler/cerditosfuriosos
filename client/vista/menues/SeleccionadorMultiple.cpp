#include "SeleccionadorMultiple.h"

SeleccionadorMultiple::SeleccionadorMultiple(int ancho,
												int alto,
												std::map<string, string> mapa) {
	set_size_request(ancho, alto);
	set_policy(Gtk::POLICY_AUTOMATIC , Gtk::POLICY_ALWAYS);
	crearBotones(mapa);
	agregarBotones();
}

SeleccionadorMultiple::SeleccionadorMultiple(int ancho,
												int alto,
												std::map<int, string> mapa) {
	set_size_request(ancho, alto);
	set_policy(Gtk::POLICY_AUTOMATIC , Gtk::POLICY_ALWAYS);
	crearBotones(mapa);
	agregarBotones();
}

SeleccionadorMultiple::~SeleccionadorMultiple() {
	int contador = 0;
	while (contador < cantidadBotones) {
		delete botones[contador];
		++contador;
	}
	delete botones;
	std::vector<Widget*> hijos = get_children();
	if (hijos.size() > 0) {
		remove();
		delete hijos[0];
	}
}

string SeleccionadorMultiple::getOpcionSeleccionada() {
	int contadorBotones = 0;
	while (botones[contadorBotones]->get_active() == false)
		++contadorBotones;
	return mapa.find(botones[contadorBotones]->get_label())->second;
}

bool SeleccionadorMultiple::hayOpcionesSeleccionables() {
	return (!mapa.empty());
}

void SeleccionadorMultiple::crearBotones(std::map<string, string> mapa) {
	this->mapa = mapa;
	botones = new Gtk::RadioButton*[mapa.size()];
	unsigned int contador = 0;
	std::map<string, string>::iterator iterador = mapa.begin();
	while (iterador != mapa.end()) {
		botones[contador] = new Gtk::RadioButton(iterador->first);
		Gtk::RadioButton::Group grupo = botones[0]->get_group();
		if (contador > 0)
			botones[contador]->set_group(grupo);
		++contador;
		++iterador;
	}
	cantidadBotones = mapa.size();
}

void SeleccionadorMultiple::crearBotones(std::map<int, string> mapa) {
	botones = new Gtk::RadioButton*[mapa.size()];
	unsigned int contador = 0;
	std::map<int, string>::iterator iterador = mapa.begin();
	while (iterador != mapa.end()) {
		stringstream ss;
		ss << iterador->first;
		botones[contador] = new Gtk::RadioButton(ss.str());
		this->mapa[botones[contador]->get_label()] = iterador->second;
		Gtk::RadioButton::Group grupo = botones[0]->get_group();
		if (contador > 0)
			botones[contador]->set_group(grupo);
		++contador;
		++iterador;
	}
	cantidadBotones = mapa.size();
}

void SeleccionadorMultiple::agregarBotones() {
	std::vector<Widget*> hijos = get_children();
	if (hijos.size() > 0) {
		remove();
		delete hijos[0];
	}
	Gtk::VBox* cajaVertical = new Gtk::VBox(false, 20);
	int contador = 0;
	while (contador < cantidadBotones) {
		cajaVertical->pack_start(*botones[contador], Gtk::PACK_SHRINK);
		++contador;
	}
	add(*cajaVertical);
}

void SeleccionadorMultiple::actualizarBotones(std::map<string, string> mapa) {
	int contador = 0;
	while (contador < cantidadBotones) {
		delete botones[contador];
		++contador;
	}
	crearBotones(mapa);
	agregarBotones();
}

void SeleccionadorMultiple::actualizarBotones(std::map<int, string> mapa) {
	int contador = 0;
	while (contador < cantidadBotones) {
		delete botones[contador];
		++contador;
	}
	crearBotones(mapa);
	agregarBotones();
}
