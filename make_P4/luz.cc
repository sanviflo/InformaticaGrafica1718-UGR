/*
Santiago Vidal Martínez	
*/
#include "luz.h"
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <file_ply_stl.h>


void Luz::activar(){
	GLfloat posf[4] = {x,y,z,tipo};
	glLightfv(t,GL_POSITION,posf);
	glEnable(GL_LIGHTING);
	glLightfv( t, GL_AMBIENT, ambiental ) ;
	glLightfv( t, GL_DIFFUSE, difusa ) ;
	glLightfv( t, GL_SPECULAR, especular ) ; 	
	glEnable(t);
}

void Luz::setPosicion(float x1,float y1, float z1){
	x=x1;
	y=y1;
	z=z1;
}

void Luz::desactivar(){
	glDisable(t);
	glDisable(GL_LIGHTING);
}

void Luz::crearLuz(float x1,float y1, float z1, GLenum t1, float amb[],float esp[], float dif[],int tip){
	x=x1;
	y=y1;
	z=z1;
	t=t1;
	tipo=tip;

	for(int i=0;i<4;i++){
		ambiental[i]=amb[i];
		especular[i]=esp[i];
		difusa[i]=dif[i];
	}
}
