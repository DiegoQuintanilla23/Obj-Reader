#include "Lector.h"
#include "Vertice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include "Matriz.h"

const char* Narch;

Lector::Lector()
{
	matTraslacion = new Matriz(0);
	RotX = new Matriz(0);
	RotY = new Matriz(0);
	RotZ = new Matriz(0);

	matTraslacion->Mat[0][0] = 1;
	matTraslacion->Mat[1][1] = 1;
	matTraslacion->Mat[2][2] = 1;
	matTraslacion->Mat[3][3] = 1;
}

Lector::~Lector()
{

}

//lee los valores numericos del archivo obj
//y los agrega a las listas
void Lector::CargarObj(const char* name)
{
	char c;
	char buffer[100];
	Narch = name;

	errno_t err = fopen_s(&obj, Narch, "r");
	if (err != 0) 
	{
		printf("Error al abrir el archivo");
		exit(0);
	}

	while (feof(obj) == 0)
	{
		fscanf_s(obj, "%c", &c, sizeof(c));
		
		if (c == '#' || c == 'o' || c == 's')
		{
			fgets(buffer, 100, obj);
		}
		else if (c == 'v')
		{
			Vertice v(0, 0, 0);
			fscanf_s(obj, "%c", &c, sizeof(c));
			fscanf_s(obj, "%f %f %f", &v.X, &v.Y, &v.Z);
			Ob.agregarVertice(v);
		}
		else if (c == 'f')
		{
			Cara f(0, 0, 0);
			fscanf_s(obj, "%c", &c, sizeof(c));
			fscanf_s(obj, "%d %d %d", &f.v1, &f.v2, &f.v3);
			Ob.agregarCara(f);
		}
	}
	fclose(obj);
}

//llena una lista de cordenadas con el contenido de las listas del objetod Ob
std::vector<float> Lector::ListaCoord()
{
	std::vector<float> coords;
	
	for (int i = 0;i < Ob.getLengthC();i++)
	{
		//printf(" %f %f %f \n", Ob.Vertices[Ob.Caras[i].v1 - 1].X, Ob.Vertices[Ob.Caras[i].v1 - 1].Y, Ob.Vertices[Ob.Caras[i].v1 - 1].Z);
		coords.push_back(Ob.Vertices[Ob.Caras[i].v1 - 1].X);
		coords.push_back(Ob.Vertices[Ob.Caras[i].v1 - 1].Y);
		coords.push_back(Ob.Vertices[Ob.Caras[i].v1 - 1].Z);

		//printf(" %f %f %f \n", Ob.Vertices[Ob.Caras[i].v2 - 1].X, Ob.Vertices[Ob.Caras[i].v2 - 1].Y, Ob.Vertices[Ob.Caras[i].v2 - 1].Z);
		coords.push_back(Ob.Vertices[Ob.Caras[i].v2 - 1].X);
		coords.push_back(Ob.Vertices[Ob.Caras[i].v2 - 1].Y);
		coords.push_back(Ob.Vertices[Ob.Caras[i].v2 - 1].Z);

		//printf(" %f %f %f \n", Ob.Vertices[Ob.Caras[i].v3 - 1].X, Ob.Vertices[Ob.Caras[i].v3 - 1].Y, Ob.Vertices[Ob.Caras[i].v3 - 1].Z);
		coords.push_back(Ob.Vertices[Ob.Caras[i].v3 - 1].X);
		coords.push_back(Ob.Vertices[Ob.Caras[i].v3 - 1].Y);
		coords.push_back(Ob.Vertices[Ob.Caras[i].v3 - 1].Z);
	}
	printf("Objeto: ");
	printf(Narch);
	printf("\n");
	return coords;
}

//multiplica una matrix por un vector y devuelve el resultado
Vertice Lector::multmat4x4vector4x1(Matriz* mat, float x, float y, float z, float w)
{
	Vertice res (0, 0, 0);
	res.X = mat->Mat[0][0] * x + mat->Mat[0][1] * y + mat->Mat[0][2] * z + mat->Mat[0][3] * w;
	res.Y = mat->Mat[1][0] * x + mat->Mat[1][1] * y + mat->Mat[1][2] * z + mat->Mat[1][3] * w;
	res.Z = mat->Mat[2][0] * x + mat->Mat[2][1] * y + mat->Mat[2][2] * z + mat->Mat[2][3] * w;
	//res.w = mat[3][0] * v.x + mat[3][1] * v.y + mat[3][2] * v.z + mat[3][3] * v.w;
	res.w = 1;
	
	return res;
}

//multiplica dos matrix 4x4 y devuelve el resultado
Matriz Lector::multmat4x4mat4x4(Matriz* mat1, Matriz* mat2)
{
	Matriz matres(0);

	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			for (int k = 0; k < 4; k++)
			{
				matres.Mat[i][j] += mat1->Mat[i][k] * mat2->Mat[k][j];
			}
		}
	}

	return matres;
}

//asigna valores a la matriz traslacion
void Lector::Traslacion(float x, float y, float z)
{
	matTraslacion->Mat[0][3] = x;
	matTraslacion->Mat[1][3] = y;
	matTraslacion->Mat[2][3] = z;
}

//asigna valores a la matriz rotacion x
void Lector::rotacionx(float grados)
{
	RotX->Mat[0][0] = 1;
	RotX->Mat[0][1] = 0;
	RotX->Mat[0][2] = 0;
	RotX->Mat[0][3] = 0;

	RotX->Mat[1][0] = 0;
	RotX->Mat[1][1] = cos(grados);
	RotX->Mat[1][2] = -sin(grados);
	RotX->Mat[1][3] = 0;

	RotX->Mat[2][0] = 0;
	RotX->Mat[2][1] = sin(grados);
	RotX->Mat[2][2] = cos(grados);
	RotX->Mat[2][3] = 0;

	RotX->Mat[3][0] = 0;
	RotX->Mat[3][1] = 0;
	RotX->Mat[3][2] = 0;
	RotX->Mat[3][3] = 1;
}

//asigna valores a la matriz rotacion y
void Lector::rotaciony(float grados)
{
	RotY->Mat[0][0] = cos(grados);
	RotY->Mat[0][1] = 0;
	RotY->Mat[0][2] = sin(grados);
	RotY->Mat[0][3] = 0;

	RotY->Mat[1][0] = 0;
	RotY->Mat[1][1] = 1;
	RotY->Mat[1][2] = 0;
	RotY->Mat[1][3] = 0;

	RotY->Mat[2][0] = -sin(grados);
	RotY->Mat[2][1] = 0;
	RotY->Mat[2][2] = cos(grados);
	RotY->Mat[2][3] = 0;

	RotY->Mat[3][0] = 0;
	RotY->Mat[3][1] = 0;
	RotY->Mat[3][2] = 0;
	RotY->Mat[3][3] = 1;
}

//asigna valores a la matriz rotacion z
void Lector::rotacionz(float grados)
{
	RotZ->Mat[0][0] = cos(grados);
	RotZ->Mat[0][1] = -sin(grados);
	RotZ->Mat[0][2] = 0;
	RotZ->Mat[0][3] = 0;

	RotZ->Mat[1][0] = sin(grados);
	RotZ->Mat[1][1] = cos(grados);
	RotZ->Mat[1][2] = 0;
	RotZ->Mat[1][3] = 0;

	RotZ->Mat[2][0] = 0;
	RotZ->Mat[2][1] = 0;
	RotZ->Mat[2][2] = 1;
	RotZ->Mat[2][3] = 0;

	RotZ->Mat[3][0] = 0;
	RotZ->Mat[3][1] = 0;
	RotZ->Mat[3][2] = 0;
	RotZ->Mat[3][3] = 1;
}
