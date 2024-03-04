/*/////////////////////////////////////////
Clase Objeto3d
Guarda dos vectores para los vertices y caras
estos serán leidos de un archivo obj
*//////////////////////////////////////////
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Vertice.h"
#include "Cara.h"

class Objeto3d
{
public:
	std::vector<Vertice> Vertices;
	std::vector<Cara> Caras;
	Objeto3d();
	virtual ~Objeto3d();
	void agregarVertice(Vertice v);
	void agregarCara(Cara c);
	int getLengthC();
	std::vector<Vertice> getlistV();
	std::vector<Cara> getlistC();

protected:

private:
};

