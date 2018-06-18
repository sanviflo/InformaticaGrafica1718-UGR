/*
Santiago Vidal Martínez	
*/
#include "objeto3d.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "octaedro.h"

Octaedro::Octaedro(float longitud){
vector<float> vertices={-longitud,-longitud,longitud,//izda abajo delante
			longitud,-longitud,longitud,//dcha abajo delante
			-longitud,-longitud,-longitud,//izda,abajo,detras
			longitud,-longitud,-longitud,//dcha,abajo,detras
			0.0,longitud,0.0,//arriba
			0.0,-longitud*2,0.0};//abajo
vector<int> caras={5,3,1,0,2,5,0,1,4,4,3,2,1,3,4,4,2,0,5,1,0,2,3,5};

Insertar(vertices,caras);
}	


