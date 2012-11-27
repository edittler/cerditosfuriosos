#include "PanelRecords.h"

PanelRecords::PanelRecords(int ancho, int alto, string ruta,
		InterfazSelectora* interfaz) : PanelImagenFondo(ancho, alto, ruta) {
	this->interfaz = interfaz;
	ventana = new Gtk::ScrolledWindow();
	botonVolver = new Gtk::Button("Volver a menu multijugador");
	cargarRecords();
	cargarVentana();
	inicializarComponentes();
}

PanelRecords::~PanelRecords() {
	delete ventana;
	delete botonVolver;
}
		
void PanelRecords::botonVolverClickeado() {
	interfaz->modoMultijugador();
}

bool comparador(pair<string, int> primero, pair<string, int> segundo) {
	return (primero.second > segundo.second);
}

void PanelRecords::cargarRecords() {
	/* Aca se cargan las partidas en el contenedor atributo de este objeto
	 * llamado "records". */
	records.push_back(pair<string, int>("Juan", 1483));
	records.push_back(pair<string, int>("Martin", 3420));
	records.push_back(pair<string, int>("Pedro", 4648));
	records.push_back(pair<string, int>("Pablo", 9549));
	records.push_back(pair<string, int>("Santiago", 4683));
	records.push_back(pair<string, int>("Maria", 4925));
	records.push_back(pair<string, int>("Juana", 428));
	records.push_back(pair<string, int>("Valeria", 8745));
	records.push_back(pair<string, int>("Ana", 2476));
	records.push_back(pair<string, int>("Florencia", 45));
	records.push_back(pair<string, int>("Agustina", 1254));
	records.push_back(pair<string, int>("Francisco", 4558));
	records.push_back(pair<string, int>("Lucas", 457));
	records.push_back(pair<string, int>("Diego", 4));
	records.push_back(pair<string, int>("Juan Cruz", 4578));
	records.push_back(pair<string, int>("Agustin", 5472));
	records.push_back(pair<string, int>("Rafael", 2455));
	records.push_back(pair<string, int>("Ignacio", 4458));
	records.push_back(pair<string, int>("Ramiro", 18541));
	records.push_back(pair<string, int>("Manuel", 4586));
	records.push_back(pair<string, int>("Carolina", 4554));
	records.push_back(pair<string, int>("Sofia", 2145));
	// Aca los ordena segun los mayores puntajes
	records.sort(comparador);
}

void PanelRecords::cargarVentana() {
	Gtk::Table* tabla = manage(new Gtk::Table(records.size(), 3, true));
	tabla->set_row_spacings(10);
	unsigned int contador = 0;
	list< pair<string, int> >::iterator iterador = records.begin();
	while (contador < records.size()) {
		std::stringstream ss;
		ss << (contador+1);
		Gtk::Label* etiquetaNumero = manage(new Gtk::Label(ss.str()));
		tabla->attach(*etiquetaNumero, 0, 1, contador, contador+1);
		Gtk::Label* etiquetaNombre = manage(new Gtk::Label(iterador->first));
		tabla->attach(*etiquetaNombre, 1, 2, contador, contador+1);
		std::stringstream ss_dos;
		ss_dos << iterador->second;
		Gtk::Label* etiquetaPuntaje = manage(new Gtk::Label(ss_dos.str()));
		tabla->attach(*etiquetaPuntaje, 2, 3, contador, contador+1);
		++iterador;
		++contador;
	}
	ventana->add(*tabla);
}

void PanelRecords::inicializarComponentes() {
	ventana->set_size_request(ANCHO_VENTANA_RECORDS, ALTO_VENTANA_RECORDS);
	ventana->set_policy(Gtk::POLICY_AUTOMATIC , Gtk::POLICY_ALWAYS);
	put(*ventana, X_VENTANA_RECORDS, Y_VENTANA_RECORDS);
	put(*botonVolver, X_BOTON_VOLVER_RECORDS, Y_BOTON_VOLVER_RECORDS);
	// Seniales
	botonVolver->signal_clicked().connect(sigc::mem_fun(*this,
										&PanelRecords::botonVolverClickeado));
}
