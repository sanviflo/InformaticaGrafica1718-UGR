/*
Santiago Vidal Martínez	
*/
#include "objeto3d.h"
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "cubo.h"

Cubo::Cubo(float longitud){

		vector<float> vertices={-longitud,longitud,longitud,//esquina superior izda delante, 0
					 longitud,longitud,longitud,//esquina superior dcha delante,1	
					-longitud,-longitud,longitud,//esquina inferior izda delante,2
					longitud,-longitud,longitud,//esquina inferior dcha delante,3
					longitud,longitud,-longitud,//esquina superior dcha detrás,4
					longitud,-longitud,-longitud,//esquina inferior dcha detrás,5
					-longitud,-longitud,-longitud,//esquina inferior izda detrás,6
					-longitud,longitud,-longitud,//esquina superior izda detrás,7
};

vector<int> caras={7,1,4,
		   1,7,0,
		   0,3,1,
		   3,0,2,
		   4,1,5,
		   5,1,3,
		   6,2,7,
		   2,0,7,
		   4,5,7,
		   7,5,6,	
		   3,2,5,
		   6,5,2
			};

		Insertar(vertices,caras);
		
}	



