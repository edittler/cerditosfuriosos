#include "Monticulo.h"
#include "Constantes.h"

Monticulo::Monticulo(b2Body* body) {
	// Defino los atributos de clase
	this->vida = M_VIDA;
	this->cuerpo = body;

	// Paso una referencia de este objeto al body de Box2D
	this->cuerpo->SetUserData(this);

	// Defino la forma del monticulo (triangulo)
	b2PolygonShape polygonShape;
	int32 verticesTriangulo = 3;

	b2Vec2 vertices[3];
	vertices[0].Set(0.0f, 0.0f);		// Vertice inferior izquierdo.
	vertices[1].Set(M_ANCHO, 0.0f);		// Vertice inferior derecho.
	vertices[2].Set((M_ANCHO)/2, M_ALTO);		// Vertice superior.

	polygonShape.Set(vertices, verticesTriangulo);

	// Defino las propiedades del cuerpo
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0.8f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = CATEGORY_MONTICULO;
	fixtureDef.filter.maskBits = MASK_MONTICULO;
	this->cuerpo->CreateFixture(&fixtureDef);
}

Monticulo::~Monticulo() {
	// TODO Auto-generated destructor stub
}

