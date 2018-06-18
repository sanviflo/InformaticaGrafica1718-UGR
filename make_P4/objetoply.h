/*
Santiago Vidal Martínez	
*/
#ifndef _OBJETOPLY_H
#define _OBJETOPLY_H
#include <vector>
#include "objetoply.h"
#include "objeto3d.h"
#include <string>

using namespace std;

class ObjetoPLY:public Objeto3D{

private:

public:
	ObjetoPLY(){}
	ObjetoPLY(string fichero){
		cargarPLY(fichero);
	}	

};
#endif
