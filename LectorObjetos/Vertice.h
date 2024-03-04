/*/////////////////////////////////////////
Clase Vertice
Guarda 3 valores float que dindican las coordenadas X,Y y Z
Objetos de esta clase seran impresos en la pantalla para
formar el obj en 3d
*//////////////////////////////////////////
/*/////////////////////////////////////////
Clase Vertice
Guarda 3 valores float para las coordenadas X, Y y Z
Estas coordenadas son leidas desde un archivo obj
*//////////////////////////////////////////
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Vertice
{
public:
	float X;
	float Y;
	float Z;
	float w;
	Vertice(float vx, float vy, float vz);
	Vertice();
	virtual ~Vertice();

protected:

private:
};

