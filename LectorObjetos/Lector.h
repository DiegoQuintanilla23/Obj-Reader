/*/////////////////////////////////////////
Clase Lector
Hace todo el proceso de lectura de una rchivo obj
y guarda sus valores en un objeto Objeto3d
Crea un vector de floats con los vertices leidos de acuerdo a las caras del archivo
*//////////////////////////////////////////
#pragma once
#include "Vertice.h"
#include "Cara.h"
#include "Objeto3d.h"
#include "Matriz.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

class Lector
{
public:
	FILE* obj;
	Objeto3d Ob;
	Matriz MM;
	Matriz* matTraslacion;
	Matriz* RotX;
	Matriz* RotY;
	Matriz* RotZ;

	Lector();
	virtual ~Lector();
	void CargarObj(const char* name);
	void printNumDBG();
	std::vector<float> ListaCoord();

	Vertice multmat4x4vector4x1(Matriz* mat, float x, float y, float z, float w);
	Matriz multmat4x4mat4x4(Matriz* mat1, Matriz* mat2);
	void Traslacion(float x, float y, float z);
	void rotacionx(float grados);
	void rotaciony(float grados);
	void rotacionz(float grados);

protected:

private:
};

