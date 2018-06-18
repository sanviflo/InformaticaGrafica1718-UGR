/*
Santiago Vidal Martínez	
*/
#ifndef _OBJETOREVOLUCION_H
#define _OBJETOREVOLUCION_H
#include <vector>
#include "objeto3d.h"
#include <string>

using namespace std;

class ObjetoRevolucion:public Objeto3D{

private:
	
public:
	ObjetoRevolucion(){}

	ObjetoRevolucion(string fichero,int nr){
		vector<float> c;
		crearObjeto(fichero,nr,c);
	}
	
	void crearObjeto(string fichero,int nr,vector<float> v);
};
#endif
