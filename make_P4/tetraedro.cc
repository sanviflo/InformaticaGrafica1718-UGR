/*
Santiago Vidal Martínez	
*/
#include "objeto3d.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "tetraedro.h"

Tetraedro::Tetraedro(float longitud){
vector<float> vertices={longitud,-(longitud-(float)25.0),((longitud+(float)20.0)*sqrt((float)3.0))/(float)2.0,//esquina inf dcha delantera, 0
-longitud,-(longitud-(float)25.0),((longitud+(float)20.0)*sqrt((float)3))/(float)2,//esquina inf izda delantera, 1
0.0,-(longitud-(float)25.0),-(((longitud+(float)20.0)*sqrt((float)3))/(float)2),//esquina inf central trasera, 2
0.0,(longitud-(float)5.0),0.0,//esquina superior,3

};
vector<int> caras={0,1,2,3,1,0,3,2,1,3,0,2};

Insertar(vertices,caras);
}	


