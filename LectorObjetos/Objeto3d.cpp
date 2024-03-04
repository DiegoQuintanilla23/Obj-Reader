#include "Objeto3d.h"
#include <stdio.h>
#include <stdlib.h>

Objeto3d::Objeto3d()
{

}

Objeto3d::~Objeto3d()
{

}

//agrega un vertice a la lista de vertices
void Objeto3d::agregarVertice(Vertice v)
{
	Vertices.push_back(v);
}

//agrega una cara a la lista de caras
void Objeto3d::agregarCara(Cara c)
{
	Caras.push_back(c);
}

//devuelve la longituz de la lista de caras
int Objeto3d::getLengthC()
{
	return Caras.size();
}

//devuelve la lista de vertices
std::vector<Vertice> Objeto3d::getlistV()
{
	return std::vector<Vertice>();
}

//devuelve la lista de caras
std::vector<Cara> Objeto3d::getlistC()
{
	return std::vector<Cara>();
}
