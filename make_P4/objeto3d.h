/*
Santiago Vidal Martínez	
*/
#ifndef _OBJETO3D_H
#define _OBJETO3D_H
#include <vector>
#include <string>
#include <GL/gl.h>
#include <GL/glut.h>
#include "JpegLoader.h"
#include <iostream>
using namespace std;

class Objeto3D{

private:
	vector<float> v;
	vector<float> v2;
	vector<int> c;
	vector<int> conex2;
	vector<int> c1;
	vector<int> c2;
	vector<float> cubiertas;
	vector<int> c_cubiertas;	
	vector<float> color_caras;
	vector<float> color_puntos;
	vector<float> color_lineas;
     	vector<float> color_ajedrez1;
   	vector<float> color_ajedrez2;
	vector<float> normales_caras;
	vector<float> normales_vertices;



	GLenum modo_suavizado=GL_SMOOTH;

	//JpegLoader imagen;
	bool tapa_activa=false;
	int n_material=0;

	//Material 1
	GLfloat mat_uso[4];
	GLfloat mat_auso[4];
	GLfloat mat_duso[4];
	GLfloat mat_euso[4];
	float brillouso;	

	//Material 1
	GLfloat mat1_emision[4]={0.0,0.0,0.0,1.0};
	GLfloat mat1_ambiente[4]={0.0215,0.1745,0.0215,1.0};
	GLfloat mat1_difuso[4]={0.07,0.61424,0.07568,1.0};
	GLfloat mat1_especular[4]={0.633,0.727811,0.633,1.0};
	float brillo=0.6*128.0;


	//Material 2
	GLfloat mat2_emision[4]={0.0,0.0,0.0,1.0};
	GLfloat mat2_ambiente[4]={0.1745,0.1745,0.1745,1.0};
	GLfloat mat2_difuso[4]={0.61424,0.04136,0.04136,1.0};
	GLfloat mat2_especular[4]={0.727811,0.626959,0.626959,1.0};
	float brillo2=0.6*128.0;

	//Material 3
	GLfloat mat3_emision[4]={0.0,0.0,0.0,1.0};
	GLfloat mat3_ambiente[4]={0.24725 ,0.1995,0.0745,1.0};
	GLfloat mat3_difuso[4]={0.75164,0.60648,0.22648,1.0};
	GLfloat mat3_especular[4]={0.628281,0.555802,0.366065,1.0};
	float brillo3=0.4*128.0;

public:
	Objeto3D(){}
	Objeto3D(vector<float> v1,vector<int> c1){
		v=v1;
		c=c1;
		CalculoNormales();
	}

	void dibujar(char mode);
	void Insertar(vector<float> v1,vector<int> c1);
	void cargarPLY(string ply);
	void poner_quitar_cubiertas();
	void invertirPuntos();
	void actualizarColores();
	void cambiarMaterialUsado(int n);
	void copiarPuntos(vector<float> p){v=p;}
	vector<float> getPuntos(){return v;}
	vector<int> getCaras(){return c;}
	vector<float> getPuntos2(){return v2;}
	vector<int> getCaras2(){return conex2;}
	void setCubiertas(vector<float> c){cubiertas=c;}
	void setCCubiertas(vector<int> c){c_cubiertas=c;}
	void modificarSuavizado();
	void reiniciar();
	void CalculoNormales();
	float getV(int pos){return v[pos];}
	int getSize(){return v.size();}

};
#endif
