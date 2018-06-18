/*
Santiago Vidal Martínez	
*/
#include "objetorevolucion.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "esfera.h"
#define PI 3.14

Esfera::Esfera(float longitud){



for(int p=0;p<360;p+=5){
	vs.push_back(longitud*sin(((p*PI)/360)));	
	vs.push_back(longitud*cos(((p*PI)/360)));
	vs.push_back(0.0);				
}	
	
//crearObjeto("",5,vs);


}	


