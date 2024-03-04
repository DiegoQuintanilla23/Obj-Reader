/*/////////////////////////////////////////
Clase cara, guarda indices para los vertices
Trabaja en conjunto con la clase vertice
Indica que vertices de un vector de vertices 
serán utilizados para formar un triangulo
*//////////////////////////////////////////
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Cara
{
public:
	int v1;
	int v2;
	int v3;
	Cara(int c1, int c2, int c3);
	virtual ~Cara();

protected:

private:
};

