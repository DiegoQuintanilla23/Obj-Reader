#include "Vertice.h"
#include <stdio.h>
#include <stdlib.h>

Vertice::Vertice(float vx, float vy, float vz)
{
	X = vx;
	Y = vy;
	Z = vz;
	w = 1;
}

Vertice::~Vertice()
{
	
}