/*
Santiago Vidal Martínez	
*/
#include "objeto_jerarquico.h"
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <file_ply_stl.h>
#include "objetoply.h"
#include "objetorevolucion.h"
#include <string>
using namespace std;

Objeto_jerarquico::Objeto_jerarquico(){
	vector<float> e;
	o2.crearObjeto("objetosRevolucion/cilindro.ply",10,e);
	o2.poner_quitar_cubiertas();
	o.cargarPLY("objetosPLY/mano1.ply");
	o3.cargarPLY("objetosPLY/mano2.ply");		
	o4.cargarPLY("objetosPLY/cuerpo.ply");
	o5.cargarPLY("objetosPLY/cabezam.ply");	

	rot=0.0;
	rot2=0.0;
	a=5.0;
	x=2.0;	
}

Objeto_jerarquico::Objeto_jerarquico(float b,float c,float d,float e){
	vector<float> r;
	o2.crearObjeto("objetosRevolucion/cilindro.ply",10,r);
	o2.poner_quitar_cubiertas();
	o.cargarPLY("objetosPLY/mano1.ply");
	o3.cargarPLY("objetosPLY/mano2.ply");		
	o4.cargarPLY("objetosPLY/cuerpo.ply");
	o5.cargarPLY("objetosPLY/cabezam.ply");	
	rot=b;
	rot2=c;
	a=d;
	x=e;
}

void Objeto_jerarquico::pintar(char modo_activo){

glEnable(GL_NORMALIZE);
glScalef(0.5,0.5,0.5);
//cabeza
		glPushMatrix();	
		glTranslatef(0.0,35.0+x,10.0);
		glScalef(0.3,0.3,0.3);
		o5.dibujar(modo_activo);
		glPopMatrix();
//cuello
		glPushMatrix();	
		glTranslatef(0.0,30.0+x/2.0,-5.0);
		glScalef(15.0,3.0+x,15.0);
		o2.dibujar(modo_activo);
		glPopMatrix();
//cuerpo
		glPushMatrix();	
		glScalef(0.3,0.3,0.3);
		o4.dibujar(modo_activo);
		glPopMatrix();
//brazo derecho
		
		glPushMatrix();
			glTranslatef(16.0,18.0,0.0);
			glScalef(1.4,1.4,1.4);
			glPushMatrix();//brazo
				glRotatef(rot2,0.0,0.0,1.0);
				glRotatef(-90.0,0.0,0.0,1.0);
				glTranslatef(0.0,6.0,0.0);				
				//glRotatef(90.0,0.0,0.0,1.0);
				glScalef(11.0,22.0,11.0);
				o2.dibujar(modo_activo);		
			glPopMatrix();	
			glPushMatrix();
				glTranslatef(11.0,-3.0+rot2/5,0.0);
				glPushMatrix(); //mano
					glTranslatef(0.0,2.0,0.0);
					glRotatef(rot,0.0,0.0,1.0);
					//glRotatef(-90.0,0.0,1.0,0.0);
					glTranslatef(12.0,0.0,0.0);
					glScalef(0.3,0.3,0.3);
					o.dibujar(modo_activo);
				glPopMatrix();	
				glTranslatef(0.0,-a,0.0);			
	glPushMatrix();
					glPushMatrix(); //yoyó
						glTranslatef(10.0,-4.0+rot/5,0.0);
						glRotatef(90.0,1.0,0.0,0.0);
						glScalef(12.0,5.0,12.0);
						o2.dibujar(modo_activo);
					glPopMatrix();
					glPushMatrix();//hilo
						glTranslatef(10.0,a/2+rot/5,0.0);
						glScalef(0.5,a,0.5);
						o2.dibujar(modo_activo);
					glPopMatrix();
				glPopMatrix();	

			glPopMatrix();
		glPopMatrix();
//brazo izdo

		glPushMatrix();
			glTranslatef(-16.0,18.0,0.0);
			glRotatef(180.0,0.0,1.0,0.0);
			glScalef(1.4,1.4,1.4);
			glPushMatrix();
				glRotatef(rot2,0.0,0.0,1.0);
				glRotatef(-90.0,0.0,0.0,1.0);
				glTranslatef(0.0,6.0,0.0);				
				//glRotatef(90.0,0.0,0.0,1.0);
				glScalef(11.0,22.0,11.0);
				o2.dibujar(modo_activo);		
			glPopMatrix();	
			glPushMatrix();
				glTranslatef(11.0,-3.0+rot2/5,0.0);
				glPushMatrix();
					glTranslatef(0.0,2.0,0.0);
					glRotatef(rot,0.0,0.0,1.0);
					//glRotatef(-90.0,0.0,1.0,0.0);
					glTranslatef(12.0,0.0,0.0);
					glRotatef(180.0,0.0,1.0,0.0);
					glScalef(0.3,0.3,0.3);
					o3.dibujar(modo_activo);
				glPopMatrix();	
				glTranslatef(0.0,-a,0.0);			
	glPushMatrix();
					glPushMatrix();
						glTranslatef(10.0,-4.0+rot/5,0.0);
						glRotatef(90.0,1.0,0.0,0.0);
						glScalef(12.0,5.0,12.0);
						o2.dibujar(modo_activo);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(10.0,a/2+rot/5,0.0);
						glScalef(0.5,a,0.5);
						o2.dibujar(modo_activo);
					glPopMatrix();
				glPopMatrix();	

			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}


void Objeto_jerarquico::asignar(float rota,float rota2,float aa,float bb){
	rot=rota;
	rot2=rota2;
	a=aa;
	x=bb;
}









