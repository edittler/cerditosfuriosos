#include <iostream>
#include "model/Escenario.h"
#include "parser/XMLTypes.h"

void probarEscenario() {
	Escenario escena;
	// Choque caja madera con pajaro y/o huevo
	escena.agregarCajaMadera(Punto2D(1,1));
	escena.agregarMonticulo(Punto2D(5, 5));
	escena.agregarCerdito(Punto2D(10, 5), Punto2D(15, 5));
	escena.habilitarSimulacion();
//	escena.lanzarPajaroRojo(Punto2D(1,3),Velocidad2D(0,-10));
	escena.lanzarHuevo(Punto2D(1,3),Velocidad2D(0,-10));
	escena.lanzarHuevo(Punto2D(5,10),Velocidad2D(0,-10));

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
}

int main(int argc, char *argv[]) {
//	probarEscenario();
//	probarParseoPunto2D();
//	probarParseoVelocidad2D();
//	probarCargaXMLEscenario();  // No incluye pajaros ni disparos.
	probarRestaurarXMLEscenario();  // Incluye pajaros y disparos.
	return 0;
}
