/*
Santiago Vidal Martínez	
*/
#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "objeto3d.h"
#include "luz.h"
#include "objetorevolucion.h"
#include "objetoply.h"
#include "objeto_jerarquico.h"
#include "tablero.h"
#include <vector>
#include <iostream>

using namespace std;


class Escena {
private:
// tamaño de los ejes
#define AXIS_SIZE 5000
Ejes ejes;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Width,Height,Front_plane,Back_plane;

private:
	char tecla=' ';
	void clear_window();
	void draw_axis();
	void draw_objects();
	int objeto_activo=0;
	char modo_activo='P';
	Luz lucecita,lucecita2;
	bool luz_activa=false;
	//Transformación de cámara
	void change_projection();
	void change_observer();
	vector<Objeto3D> v;
	Tablero tablero;
	char tipo_obj='0';
	int obj_cargado=-1;
	string objeto1,objeto2;
	char tapa='y';
	bool esta=false;
	vector<float> c;
	bool esta_cargado=false;
	int material_activo=0;
	int segmentos=2;
	bool esta2=false;
	float aumento=4.5;
	float cuello=2.0;
	float rot=0.0,a=5.0,rot2=0.0;
	bool yoyoabajo=false,yoyoarriba=true,cuello_arriba=false,cuello_abajo=true,mano_arriba=false,mano_abajo=true,brazo_arriba=false,brazo_abajo=true;
	float b1=0.8;
	float b2=0.8;
	float b3=0.8;
	float b4=0.6;
	bool textura=false;
	bool cambio_suavizado=false;
	ObjetoRevolucion p;
	ObjetoPLY q;
	Objeto_jerarquico mario;
	float lx=99999.0,ly=999999.0,lz=99999999.0,lx1=-99999999.0,ly1=99999999.0,lz1=99999999.0,lx2=-99999999.0,ly2=99999999.0,lz2=-99999999.0,lx3=99999999.0,ly3=99999999.0,lz3=-99999999.0;

float px=0.0,py=0.0,pz=10000.0,px1=-10000.0,py1=0.0,pz1=0.0,px2=0.0,py2=0.0,pz2=-10000.0,px3=10000.0,py3=0.0,pz3=0.0;
	float l1=lx,l2=ly,l3=lz,p1=px,p2=py,p3=pz;
	int pos=0,pos2=0;

public:
     Escena();
	void inicializar(int UI_window_width,int UI_window_height);
	void redimensionar(int newWidth,int newHeight) ;
	void modifica();// Dibujar
	void dibujar() ;
	char getTecla(){return tecla;}
	// Interacción con la escena
	int teclaPulsada(unsigned char Tecla1,int x,int y) ;
	void teclaEspecial(int Tecla1,int x,int y);	
	void cambiarPosLuz1();
	void cambiarPosLuz2();
};
#endif
