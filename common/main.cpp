#include <iostream>
#include "model/Escenario.h"
#include "parser/XMLTypes.h"
#include "communication/MensajeCliente.h"
#include "communication/MensajeServer.h"
#include "communication/RespuestaServer.h"
#include "communication/Evento.h"

void probarEscenario() {
	Escenario escena;
	// Choque caja madera con pajaro y/o huevo
	escena.agregarCajaMadera(Punto2D(1,1));
	escena.agregarMonticulo(Punto2D(5, 5));
	unsigned int id = Escenario::generarId();
	escena.agregarCerdito(Punto2D(10, 5), Punto2D(15, 5), id);

	escena.habilitarSimulacion();
//	escena.lanzarPajaroRojo(Punto2D(1,3),Velocidad2D(0,-10));

	// choque en y de pajaro y huevo (en 4ta iteracion)
//	escena.lanzarPajaroRojo(Punto2D(10, 15), Velocidad2D(0, -20));
//	escena.lanzarHuevoBlanco(Punto2D(10, 12), Velocidad2D(0, 20));

	// choque de dos pajaros (en 5ta iteracion)
//	escena.lanzarPajaroRojo(Punto2D(5, 3), Velocidad2D(20, 30));
//	escena.lanzarPajaroRojo(Punto2D(9, 3), Velocidad2D(-20, 30));

	// restitucion - se calcula segun la velocidad y parametro de restitucion
//	escena.lanzarPajaroRojo(Punto2D(5, 2), Velocidad2D(0, -20));
//	escena.lanzarPajaroRojo(Punto2D(10, 0.9), Velocidad2D(0, 0));

	// choque con bordes (en 2ra iteracion)
//	escena.lanzarHuevoBlanco(Punto2D(5, 3), Velocidad2D(0, 10));
//	escena.lanzarPajaroRojo(Punto2D(5.1, 5), Velocidad2D(0, -10));

	for(int i = 0; i < 50; i++) {
		escena.correrTick();
		getchar();  // tecla para continuar.
	}
}

void probarParseoPunto2D() {
	std::cout << " === PROBANDO SERIALIZACION DE PUNTO 2D ===" << std::endl;
	std::cout << "\t=== GUARDANDO PUNTO 2D ===" << std::endl;
	XMLDocument doc1;
	XMLDeclaration* decl = new XMLDeclaration( "1.0", "UTF-8", "");
	// Creo un punto 2D
	Punto2D punto(4.56339, 6.32564);
	doc1.LinkEndChild(decl);
	doc1.LinkEndChild(punto.serialize());
	doc1.SaveFile("punto2d.xml");
	std::cout << "\t=== CARGANDO PUNTO 2D ===" << std::endl;
	XMLDocument doc2;
	doc2.LoadFile("punto2d.xml");
	XMLNode* raiz = doc2.RootElement();
	Punto2D p(raiz);
	std::cout << "\tPunto cargado:  x= " << p.x << "  y= " << p.y << std::endl;
}

void probarParseoVelocidad2D() {
 	std::cout << " === PROBANDO SERIALIZACION DE VELOCIDAD 2D ===" << std::endl;
 	std::cout << "\t=== GUARDANDO VELOCIDAD 2D ===" << std::endl;
 	XMLDocument doc1;
 	XMLDeclaration* decl = new XMLDeclaration( "1.0", "UTF-8", "");
 	// Creo una velocidad 2D
 	Velocidad2D vel(4.56339, 6.32564);
 	doc1.LinkEndChild(decl);
 	doc1.LinkEndChild(vel.serialize());
 	doc1.SaveFile("velocidad2d.xml");
 	std::cout << "\t=== CARGANDO VELOCIDAD 2D ===" << std::endl;
 	XMLDocument doc2;
 	doc2.LoadFile("velocidad2d.xml");
 	XMLNode* raiz = doc2.RootElement();
 	Velocidad2D v(raiz);
 	std::cout << "\tPunto cargado: x= " << v.x << " y= " << v.y << std::endl;
}

void probarCargaXMLEscenario() {
	std::cout << " === PROBANDO LA CARGA DEL ESCENARIO A PARTIR DE UN ARCHIVO XML ===" << std::endl;
	// Declaro el escenario que donde voy a cargar el XML.
	Escenario escena;
	// Declaro y cargo el documento XML.
	XMLDocument doc;
	std::string fileName = "MiMundo-level1.xml";
	bool cargoArchivo = doc.LoadFile(fileName);

	// Si no se cargo, lanzo error.
	if (cargoArchivo == false) {
		std::cout << "\tError al abrir el archivo XML." << std::endl;
	} else {
		// Obtengo el elemento raiz, que debe ser <Nivel>, pero no valido.
		const XMLNode* nodo = doc.RootElement();
		// Obtengo el primer elemento hijo que debe ser <Escenario>
		nodo = nodo->FirstChildElement();
		// Cargo el escenario a partir del nodo XML.
		escena.hydrate(nodo);
	}

	// AHORA PRUEBO GUARDAR EL ESCENARIO
	XMLDocument docSave;
	XMLDeclaration* decl = new XMLDeclaration( "1.0", "UTF-8", "");
	docSave.LinkEndChild(decl);
	docSave.LinkEndChild(escena.serialize());
	docSave.SaveFile("guardado.xml");
}

void probarRestaurarXMLEscenario() {
	std::cout << " === PROBANDO LA RESTAURACION DEL ESCENARIO A PARTIR DE UN ARCHIVO XML ===" << std::endl;
	// Declaro el escenario que donde voy a cargar el XML.
	Escenario escena;
	// Declaro y cargo el documento XML.
	XMLDocument doc;
	std::string fileName = "MiMundo-restore.xml";
	bool cargoArchivo = doc.LoadFile(fileName);
	// Si no se cargo, lanzo error.
	if (cargoArchivo == false) {
		std::cout << "\tError al abrir el archivo XML." << std::endl;
	} else {
		// Obtengo el elemento raiz, que debe ser <Nivel>, pero no valido.
		const XMLNode* nodo = doc.RootElement();
		// Obtengo el primer elemento hijo que debe ser <Escenario>
		nodo = nodo->FirstChildElement();
		// Cargo el escenario a partir del nodo XML.
		escena.hydrate(nodo);
	}

	// AHORA PRUEBO GUARDAR EL ESCENARIO
	XMLDocument docSave;
	XMLDeclaration* decl = new XMLDeclaration( "1.0", "UTF-8", "");
	docSave.LinkEndChild(decl);
	docSave.LinkEndChild(escena.serialize());
	docSave.SaveFile("restauracion-guardado.xml");
}

void probarReanudarXMLEscenario() {
	std::cout << " === PROBANDO LA REANUDACION DEL ESCENARIO A PARTIR DE UN ARCHIVO XML ===" << std::endl;
	// Declaro el escenario que donde voy a cargar el XML.
	Escenario escena;
	// Declaro y cargo el documento XML.
	XMLDocument doc;
	std::string fileName = "restauracion-guardado.xml";
	bool cargoArchivo = doc.LoadFile(fileName);
	// Si no se cargo, lanzo error.
	if (cargoArchivo == false) {
		std::cout << "\tError al abrir el archivo XML." << std::endl;
	} else {
		// Obtengo el elemento raiz, que debe ser <Nivel>, pero no valido.
		const XMLNode* nodo = doc.RootElement();
		// Cargo el escenario a partir del nodo XML.
		escena.hydrate(nodo);
	}
}

void probarSerializarEvento() {
	// Serializo un evento no definido
	Evento eNoDefinido;
	std::string strNoDefinido = eNoDefinido.serealizar();
	if (strNoDefinido.empty())
		std::cout << "La cadena evento indefinido está vacia" << std::endl;
	// Deserealizo el evento no definido
	Evento eDesIndef(strNoDefinido);
	if (eDesIndef.getTipoEvento() == E_INDEFINIDO) {
		std::cout << "Deserealizar evento indefinido                 OK" << std::endl;
	} else {
		std::cout << "Deserealizar evento indefinido                 FAIL" << std::endl;
	}

	// Serealizo un pedido de disparo indefinido.
	Evento ePedidoDisparoInd(T_DISPARO_INDEFINIDO, Punto2D(1.2, 3.4), Velocidad2D(3.43, 5.67));
	std::string strPedidoDisparoIn = ePedidoDisparoInd.serealizar();
	if (strPedidoDisparoIn.empty())
		std::cout << "La cadena de pedido de disparo indefinido está vacia" << std::endl;

	// Serealizo un pedido de disparo de huevo blanco.
	Evento ePedidoDisparoHB(T_HUEVO_BLANCO, Punto2D(1.2f, 3.4f), Velocidad2D(3.43, 5.67));
	std::string strPedidoDisparoHB = ePedidoDisparoHB.serealizar();
	std::cout << strPedidoDisparoHB << std::endl;
	Evento eDesPedidoDisparoHB(strPedidoDisparoHB);
	if (strPedidoDisparoHB.compare(eDesPedidoDisparoHB.serealizar()) == 0) {
		std::cout << "Deserealizar evento pedido disparo huevo       OK" << std::endl;
	} else {
		std::cout << "Deserealizar evento pedido disparo huevo       FAIL" << std::endl;
	}

	// Serializo correr tick
	Evento eTick(E_CORRER_TICK);
	std::string strTick = eTick.serealizar();
	std::cout << strTick << std::endl;
	Evento eSerTick(strTick);
	if (eSerTick.getTipoEvento() == E_CORRER_TICK) {
		std::cout << "Deserealizar evento correr tick                OK" << std::endl;
	} else {
		std::cout << "Deserealizar evento correr tick                FAIL" << std::endl;
	}

	// Serealizo un disparo indefinido.
	Evento eDisparoI(T_DISPARO_INDEFINIDO, Punto2D(1.2f, 3.4f), Velocidad2D(0.34f, 4.34f));
	std::string strDisparoInd = eDisparoI.serealizar();
	if (strDisparoInd.empty())
		std::cout << "La cadena de disparo indefinido está vacia" << std::endl;

	// Serealizo un disparo de huevo codorniz.
	Evento eDisparoHC(T_HUEVO_CODORNIZ, Punto2D(1.2f, 3.4f), Velocidad2D(0.34f, 4.34f));
	std::string strDisparoHC = eDisparoHC.serealizar();
	std::cout << strDisparoHC << std::endl;
	Evento eDesDisparoHC(strDisparoHC);
	if (strDisparoHC.compare(eDesDisparoHC.serealizar()) == 0) {
		std::cout << "Deserealizar evento disparo huevo              OK" << std::endl;
	} else {
		std::cout << "Deserealizar evento disparo huevo              FAIL" << std::endl;
	}

	// Serealizo un pajaro indefinido.
	Evento ePajaroI(T_PAJARO_INDEFINIDO, Punto2D(2.45, 3.45), Velocidad2D(0.34f, 4.34f));
	std::string strPajaroInd = ePajaroI.serealizar();
	if (strPajaroInd.empty())
		std::cout << "La cadena de pajaro indefinido está vacia" << std::endl;

	// Serealizo un pajaro verde.
	Evento ePajaroV(T_PAJARO_VERDE, Punto2D(2.45, 3.45), Velocidad2D(0.34f, 4.34f));
	std::string strPajaroV = ePajaroV.serealizar();
	std::cout << strPajaroV << std::endl;
	Evento eDesPajaroV(strPajaroV);
	if (strPajaroV.compare(eDesPajaroV.serealizar()) == 0) {
		std::cout << "Deserealizar evento lanzamiento pajaro         OK" << std::endl;
	} else {
		std::cout << "Deserealizar evento lanzamiento pajaro         FAIL" << std::endl;
	}

	// Serializo fin de nivel
	Evento eFinNivel(E_FIN_NIVEL);
	std::string strFinNivel = eFinNivel.serealizar();
	std::cout << strFinNivel << std::endl;
	Evento eDesFinNivel(strFinNivel);
	if (eDesFinNivel.getTipoEvento() == E_FIN_NIVEL) {
		std::cout << "Deserealizar evento fin nivel                  OK" << std::endl;
	} else {
		std::cout << "Deserealizar evento fin nivel                  FAIL" << std::endl;
	}
}

void probarSerializarMensajeCliente() {
	// Creo un mensaje no definido
	MensajeCliente msjND;
	std::string msj = msjND.serealizar();
	if (msj[0] == '\n')
			std::cout << "La cadena de mensaje indefinido está vacia" << std::endl;

	// Creo un mensaje para solicitar ver records.
	MensajeCliente msjVR(MC_VER_RECORDS);
	msj = msjVR.serealizar();
	std::cout << msj;
	MensajeCliente msjVRD;
	msjVRD.deserealizar(msj);
	if (msjVRD.serealizar().compare(msjVR.serealizar()) == 0) {
		std::cout << "Deserealizar mensaje ver records               OK" << std::endl;
	} else {
		std::cout << "Deserealizar mensaje ver records               FAIL" << std::endl;
	}

	// Creo un mensaje para solicitar ver los mundos disponibles.
	MensajeCliente msjVM(MC_VER_MUNDOS);
	msj = msjVM.serealizar();
	std::cout << msj;
	MensajeCliente msjVMD;
	msjVMD.deserealizar(msj);
	if (msjVMD.serealizar().compare(msjVM.serealizar()) == 0) {
		std::cout << "Deserealizar mensaje ver mundos                OK" << std::endl;
	} else {
		std::cout << "Deserealizar mensaje ver mundos                FAIL" << std::endl;
	}

	// Creo un mensaje para solicitar crear una partida.
	MensajeCliente msjCP("El Mundo", "La Banda de los Cerditos Locos");
	msj = msjCP.serealizar();
	std::cout << msj;
	MensajeCliente msjCPD;
	msjCPD.deserealizar(msj);
	if (msjCPD.serealizar().compare(msjCP.serealizar()) == 0) {
		std::cout << "Deserealizar mensaje crear partida             OK" << std::endl;
	} else {
		std::cout << "Deserealizar mensaje crear partida             FAIL" << std::endl;
	}

	// Creo un mensaje para solicitar unirse a una partida.
	MensajeCliente msjUP("La Banda de los Cerditos Locos");
	msj = msjUP.serealizar();
	std::cout << msj;
	MensajeCliente msjUPD;
	msjUPD.deserealizar(msj);
	if (msjUPD.serealizar().compare(msjUP.serealizar()) == 0) {
		std::cout << "Deserealizar mensaje unirse partida            OK" << std::endl;
	} else {
		std::cout << "Deserealizar mensaje unirse partida             FAIL" << std::endl;
	}

	// Creo un mensaje para enviar un evento
	Evento pedidoDisparo(T_HUEVO_BLANCO, Punto2D(1.2f, 3.4f), Velocidad2D(3.43, 5.67));
	MensajeCliente msjE(pedidoDisparo);
	msj = msjE.serealizar();
	std::cout << msj;
	MensajeCliente msjED;
	msjED.deserealizar(msj);
	if (msjED.serealizar().compare(msjE.serealizar()) == 0) {
		std::cout << "Deserealizar mensaje con evento                 OK" << std::endl;
	} else {
		std::cout << "Deserealizar mensaje con evento                 FAIL" << std::endl;
	}
}

void probarSerializacionMensajeServer() {
	Evento unEvento(E_CORRER_TICK);
	MensajeServer* msj1 = new MensajeServer(unEvento);
	std::string sMS = msj1->serealizar();
	MensajeServer msj2;
	msj2.deserealizar(sMS);
	std::string sEvento = unEvento.serealizar();
	std::cout << unEvento.serealizar() << std::endl;
	std::cout << msj2.getEvento().serealizar() << std::endl;
	if (unEvento.serealizar().compare(msj2.getEvento().serealizar()) == 0) {
		std::cout << "Deserealizar MS evento                         OK" << std::endl;
	} else {
		std::cout << "Deserealizar MS evento                         FAIL" << std::endl;
	}
}

void probarXMLString() {
	std::cout << " === PROBANDO OBTENER XML EN UN STRING ===" << std::endl;
	// Declaro y cargo el documento XML.
	XMLDocument doc;
	std::string fileName = "MiMundo-level1.xml";
	bool cargoArchivo = doc.LoadFile(fileName);
	// Si no se cargo, lanzo error.
	if (cargoArchivo == false) {
		std::cout << "\tError al abrir el archivo XML." << std::endl;
		return;
	}
	TiXmlPrinter printer;
	printer.SetIndent("");
	printer.SetLineBreak("");
	doc.Accept(&printer);
	std::string xml = printer.CStr();
	std::cout << "Tamaño string xml: " << xml.size() << std::endl;
	std::cout << "XML:\n" << xml;

	XMLDocument doc1;
	doc.Parse(xml.c_str(), 0, TIXML_ENCODING_UTF8);
	doc.SaveFile("xmlstring.xml");
}

int main(int argc, char *argv[]) {
//	probarEscenario();
//	probarParseoPunto2D();
//	probarParseoVelocidad2D();
//	probarCargaXMLEscenario();  // No incluye pajaros ni disparos.
//	probarRestaurarXMLEscenario();  // Incluye pajaros y disparos.
//	probarReanudarXMLEscenario();
//	probarSerializarEvento();
	probarSerializarMensajeCliente();
//	probarSerializacionMensajeServer();
//	probarXMLString();
	return 0;
}
