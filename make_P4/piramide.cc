/*
Santiago Vidal Martínez	
*/
#include "objeto3d.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "piramide.h"

Piramide::Piramide(float longitud){
vector<float> vertices={-longitud,-longitud,longitud,//izda abajo delante
			longitud,-longitud,longitud,//dcha abajo delante
			-longitud,-longitud,-longitud,//izda,abajo,detras
			longitud,-longitud,-longitud,//dcha,abajo,detras
			0.0,longitud,0.0};//arriba
vector<int> caras={1,3,4,4,2,0,2,1,0,1,2,3,0,1,4,4,3,2};

Insertar(vertices,caras);
}	


