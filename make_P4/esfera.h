/*
Santiago Vidal Martínez	
*/
#ifndef _ESFERA_H
#define _ESFERA_H
#include <vector>
#include "objetorevolucion.h"

using namespace std;

class Esfera:public ObjetoRevolucion{

private:
	vector<float> vs;
public:
	Esfera(float longitud);	
	vector<float> getVS(){return vs;}
};
#endif
