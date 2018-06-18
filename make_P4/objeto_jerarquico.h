/*
Santiago Vidal Martínez	
*/
#ifndef _OBJETO_JERARQUICO_H
#define _OBJETO_JERARQUICO_H
#include <vector>
#include <string>
#include "objetoply.h"
#include "objetorevolucion.h"
#include "objeto3d.h"
using namespace std;

class Objeto_jerarquico:public Objeto3D{

private:

	ObjetoPLY o,o3,o4,o5;
	ObjetoRevolucion o2;
	float rot;
	float rot2;
	float a;
	float x;

public:
	Objeto_jerarquico();
	Objeto_jerarquico(float b,float c,float d,float e);
	void pintar(char modo_activo);
	void asignar(float rota,float rota2,float aa,float bb);
};
#endif
