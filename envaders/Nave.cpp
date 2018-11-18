#include "Nave.h"



Nave::Nave()
{
}


Nave::~Nave()
{
}



float * Nave::GetVertices()
{
	float *n = vertices;
	return n;
}

int Nave::getSizeVec()
{
	int s = sizeof(vertices);
	return s;
}
