/*
Santiago Vidal Martínez	
*/
#ifndef _TABLERO_H
#define _TABLERO_H
#include <vector>
#include "objeto3d.h"

using namespace std;

class Tablero:public Objeto3D{

private:
	GLuint idTex;
	vector<float> ctv;
	bool activado=false;
public:
	Tablero(){}
	Tablero(int longitud);
	GLuint LoadBMP(const char * imagepath);
	void Textura();
	void setActivo(bool text){activado=text;}
};
#endif
