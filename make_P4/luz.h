/*
Santiago Vidal Martínez	
*/
#ifndef _LUZ_H
#define _LUZ_H
#include <vector>
#include <string>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

class Luz{

private:
	float x,y,z;
	float pos[4];
	float ambiental[4];
	float especular[4];
	float difusa[4];
	GLenum t; 
	float tipo=1.0;
	
public:

	Luz(){}	
	void crearLuz(float x1,float y1, float z1, GLenum t1, float amb[],float esp[], float dif[],int tip);
	void setPosicion(float x1,float y1, float z1);
	void activar();
	void desactivar();

};
#endif
