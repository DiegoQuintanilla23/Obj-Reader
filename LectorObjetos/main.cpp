/*/////////////////////////////////////////
PROYECTO GRAFICACION
LECTOR DE OBJ
FECHA DE ENTREGA: 30/05/23

JUAN DIEGO QUINTANILLA ESCALANTE
*//////////////////////////////////////////
//#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Lector.h"
#include "Vertice.h"
#include <cmath>

Lector obj1, obj2, obj3;						//lectores de objetos
std::vector<float> coords1, coords2, coords3;	//coordenadas de cada objeto
float t = 0.0f;									//variable t obj 1 (bezier)
float gr = 0.0f;								//grados obj 2 (rotacion)
Vertice v(0, 0, 0);								//Vertice para la impresion de los triangulos
Vertice vv(0, 0, 0);							//Vertice para la impresion de los triangulos
Vertice vvv(0, 0, 0);							//Vertice para la impresion de los triangulos
Vertice v2(0, 0, 0);							//Usada en rotacion
int flag = 0;									//variable para cambio de color de obj2

float RGB[] = { 1.0, 1.0, 1.0 };				//Iluminacion global
float Cobj1[] = { 1.0, 0.5, 0.0 };				//Color Objeto 1
float Cobj2[] = { 0.0, 0.5, 1.0 };				//Color objeto 2
float Cobj3[] = { 0.5215, 0.3215, 0.0 };		//Color objeto 3

float normalGLB[] = { 0.0, 0.0, 0.0 };			//Arreglo para guardar normales
float foco[] = { 1.5, 1.3, 1.5 };				//iluminacion
float Col[] = { 0.0, 0.0, 0.0 };				//Punto hacia donde ve
float FC[] = { 0.0, 0.0, 0.0 };					//vector direccion luz
float D = 0.0f;									//factor para la iluminacion

/*
Funcion para rotar vertices
Devuelve un vertice como resultado de la multiplicacion de matrices
*/
Vertice Rotar(Vertice pt)
{
	Vertice vert(0, 0, 0);
	obj2.Traslacion(v2.X, v2.Y, v2.Z);
	obj2.rotaciony(gr);
	obj2.MM = obj2.multmat4x4mat4x4(obj2.matTraslacion, obj2.RotY);

	obj2.Traslacion(-1.0f * (v2.X), -1.0f * (v2.Y), -1.0f * (v2.Z));

	obj2.MM = obj2.multmat4x4mat4x4(&obj2.MM, obj2.matTraslacion);

	vert = obj2.multmat4x4vector4x1(&obj2.MM, pt.X, pt.Y, pt.Z, pt.w);
	return vert;
}

/*
Funcion para calcular el siguiente punto en la curva de bezier
devuelve un objeto Vertice
el factor t es global
*/
Vertice Bezier(Vertice pt)
{
	Vertice v(0, 0, 0);
	v.X = pow((1 - t), 3) * pt.X + 3 * pow((1 - t), 2) * t * (pt.X + 2) + 3 * pow((1 - t) * t, 2) * (pt.X + 5) + pow(t, 3) * (pt.X + 5);
	v.Y = pow((1 - t), 3) * pt.Y + 3 * pow((1 - t), 2) * t * (pt.Y + 7) + 3 * pow((1 - t) * t, 2) * (pt.Y + 10) + pow(t, 3) * (pt.Y);
	v.Z = pow((1 - t), 3) * pt.Z + 3 * pow((1 - t), 2) * t * pt.Z + 3 * pow((1 - t) * t, 2) * pt.Z + pow(t, 3) * (pt.Z);
	return v;
}

/*
Funcion para calcular el factor de iluminacion de un triangulo
Recibe las cordenadas XYZ de 3 ountos (el triangulo) en floats
Calcula la normal, vctor de direccion del foco y normaliza ambos para multiplicarlos
Devuelve un float
*/
float Iluminacion(float A1, float A2, float A3, float B1,float B2, float B3, float C1, float C2, float C3)
{
	float U[3];
	float V[3];
	float aux;
	U[0] = B1 - A1;
	U[1] = B2 - A2;
	U[2] = B3 - A3;
	V[0] = C1 - A1;
	V[1] = C2 - A2;
	V[2] = C3 - A3;

	normalGLB[0] = (U[1] * V[2]) - (U[2] * V[1]);
	normalGLB[1] = ((U[0] * V[2]) - (U[2] * V[0]))*(-1);
	normalGLB[2] = (U[0] * V[1]) - (U[1] * V[0]);

	normalGLB[0] = normalGLB[0] * (-1);
	normalGLB[1] = normalGLB[1] * (-1);
	normalGLB[2] = normalGLB[2] * (-1);

	FC[0] = Col[0] - foco[0];
	FC[1] = Col[1] - foco[1];
	FC[2] = Col[2] - foco[2];

	aux = sqrt(powf(normalGLB[0], 2) + powf(normalGLB[1], 2) + powf(normalGLB[2], 2));
	normalGLB[0] = normalGLB[0] / aux;
	normalGLB[1] = normalGLB[1] / aux;
	normalGLB[2] = normalGLB[2] / aux;

	aux = sqrt(powf(FC[0], 2) + powf(FC[1], 2) + powf(FC[2], 2));
	FC[0] = FC[0] / aux;
	FC[1] = FC[1] / aux;
	FC[2] = FC[2] / aux;

	aux = (normalGLB[0] * FC[0]) + (normalGLB[1] * FC[1]) + (normalGLB[2] * FC[2]);
	return abs(aux);
}

void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//le dice que va dibujar
	//GL_QUADS
	//GL_TRIANGLES
	glBegin(GL_TRIANGLES);

	/*
	Antes de dibujarlos los tienen que transformar
	1.generar todas sus matrices de transformacion
	2.multiplicacarlas en orden inverso para sacar la matriz modelo
	3.multiplicar la matriz del modelo por cada vertice cuando leo los vertices y antes de dibujarlos
	hacer un cluclo de dibuja
	variable global para hacer el ciclo en display
	*/

	//Objeto 1 (Raichu)
	for (int i = 0;i < coords1.size();i += 9)
	{
		v.X = coords1[i];
		v.Y = coords1[i + 1];
		v.Z = coords1[i + 2];
		v = Rotar(v);

		vv.X = coords1[i + 3];
		vv.Y = coords1[i + 4];
		vv.Z = coords1[i + 5];
		vv = Rotar(vv);

		vvv.X = coords1[i + 6];
		vvv.Y = coords1[i + 7];
		vvv.Z = coords1[i + 8];
		vvv = Rotar(vvv);

		D = Iluminacion(v.X, v.Y, v.Z, vv.X, vv.Y, vv.Z, vvv.X, vvv.Y, vvv.Z);
		glColor3f(D * RGB[0] * Cobj1[0], D * RGB[1] * Cobj1[1], D * RGB[2] * Cobj1[2]);

		glVertex3f(v.X, v.Y, v.Z);
		glVertex3f(vv.X, vv.Y, vv.Z);
		glVertex3f(vvv.X, vvv.Y, vvv.Z);
	}

	//Objeto 2 (lightning bolt)
	for (int i = 0;i < coords2.size();i += 9)
	{
		v.X = coords2[i];
		v.Y = coords2[i + 1];
		v.Z = coords2[i + 2];
		v = Bezier(v);
		v = Rotar(v);

		vv.X = coords2[i + 3];
		vv.Y = coords2[i + 4];
		vv.Z = coords2[i + 5];
		vv = Bezier(vv);
		vv = Rotar(vv);

		vvv.X = coords2[i + 6];
		vvv.Y = coords2[i + 7];
		vvv.Z = coords2[i + 8];
		vvv = Bezier(vvv);
		vvv = Rotar(vvv);

		D = Iluminacion(v.X, v.Y, v.Z, vv.X, vv.Y, vv.Z, vvv.X, vvv.Y, vvv.Z);
		glColor3f(D * RGB[0] * Cobj2[0], D * RGB[1] * Cobj2[1], D * RGB[2] * Cobj2[2]);

		glVertex3f(v.X, v.Y, v.Z);
		glVertex3f(vv.X, vv.Y, vv.Z);
		glVertex3f(vvv.X, vvv.Y, vvv.Z);
	}

	//objeto 3 (base)
	for (int i = 0;i < coords3.size();i += 9)
	{
		D = Iluminacion(coords3[i], coords3[i + 1], coords3[i + 2], coords3[i + 3], coords3[i + 4], coords3[i + 5], coords3[i + 6], coords3[i + 7], coords3[i + 8]);
		glColor3f(D * RGB[0] * Cobj3[0], D * RGB[1] * Cobj3[1], D * RGB[2] * Cobj3[2]);
		v.X = coords3[i];
		v.Y = coords3[i + 1];
		v.Z = coords3[i + 2];
		glVertex3f(v.X, v.Y, v.Z);
		v.X = coords3[i + 3];
		v.Y = coords3[i + 4];
		v.Z = coords3[i + 5];
		glVertex3f(v.X, v.Y, v.Z);
		v.X = coords3[i + 6];
		v.Y = coords3[i + 7];
		v.Z = coords3[i + 8];
		glVertex3f(v.X, v.Y, v.Z);
	}
	glEnd();

	//condicional para la manipulacion del factor t
	if (t <= 2)
	{
		t += 0.005f;
	}
	else
	{
		t = 0.0f;
		if (flag == 0)
		{
			Cobj2[0] = 0.0;
			Cobj2[1] = 0.7803;
			Cobj2[2] = 1.0;
			flag = 1;
		}
		else
		{
			Cobj2[0] = 1.0;
			Cobj2[1] = 0.8588;
			Cobj2[2] = 0.0;
			flag = 0;
		}
	}

	//condicional para la manípulacion de los grados para la rotacion
	if (gr < 6.28319)//360 en RAD
	{
		gr+=0.001f;
	}
	else
	{
		gr = 0.0f;
	}
	
	glutSwapBuffers();
	glFlush();
}

void init(void)
{
	/*  select clearing (background) color       */
	//0-1
	glClearColor(0.7372, 0.7960, 1.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_EQUAL);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Angulo, aspecto (dimensiones), plano z cercano y plano z lejano
	gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//camara
	gluLookAt(10.0, 8.0, 17.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//Funcion para cambiar el color del objeto 1 con las teclas direccionales
void processSpecialKeys(int key, int x, int y) 
{
	switch (key) 
	{
		case GLUT_KEY_UP:
			Cobj1[0] = 1.0;
			Cobj1[1] = 0.5;
			Cobj1[2] = 0.0;
			break;
		case GLUT_KEY_DOWN:
			Cobj1[0] = 1.0;
			Cobj1[1] = 0.0;
			Cobj1[2] = 0.0;
			break;
		case GLUT_KEY_RIGHT:
			Cobj1[0] = 0.0;
			Cobj1[1] = 1.0;
			Cobj1[2] = 0.0;
			break;
		case GLUT_KEY_LEFT:
			Cobj1[0] = 0.0;
			Cobj1[1] = 1.0;
			Cobj1[2] = 1.0;
			break;
	}
}

//Funcion para hacer el uso del raton
void myMouseHandleFunction(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//printf("click");
		Cobj1[0] += 0.1;
		Cobj1[1] += 0.1;
		Cobj1[2] += 0.1;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		Cobj1[0] -= 0.1;
		Cobj1[1] -= 0.1;
		Cobj1[2] -= 0.1;
	}
}

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
	//inicializar glut
	glutInit(&argc, argv);

	//Crean una ventana, detecta el so y crea la ventana
	//caracteristicas para el renderizado de la ventana
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	//tama�o en pixeles
	glutInitWindowSize(800, 600);
	//posicion de la ventana en pixeles
	glutInitWindowPosition(100, 100);
	//crea la ventana y la muestra, con el titulo en parametro
	glutCreateWindow("Lector de Objetos");

	// Funciones para teclas y raton
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(myMouseHandleFunction);

	obj1.CargarObj("Raichu.obj");
	coords1 = obj1.ListaCoord();

	obj2.CargarObj("lithning.obj");
	coords2 = obj2.ListaCoord();

	v2.X = 0.0f;
	v2.Y = 0.0f;
	v2.Z = 0.0f;

	obj3.CargarObj("base.obj");
	coords3 = obj3.ListaCoord();
	init();

	//hace el display y hace un ciclo 
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}