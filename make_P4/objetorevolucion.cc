/*
Santiago Vidal Martínez	
*/
#include "objeto3d.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "objetorevolucion.h"
#include <string>
#define PI 3.14159265


void ObjetoRevolucion::crearObjeto(string fichero,int nr,vector<float> v){
	//vector<float> v1={5.0,5.0,0.0,
	//		5.0,0.0,0.0,
	//		5.0,-5.0,0.0
	//		};
	reiniciar();
	vector<float> v1;
	if(v.size()==0){
		cargarPLY(fichero);
		if(getPuntos().at(1)<getPuntos().at(getPuntos().size()-3))
			invertirPuntos();
		v1=getPuntos();
	}
	else{
		v1=v;
	}	
	vector<float> v2;
	vector<int> c1;	
	vector<float> aux,aux2;
	int contador=0;
	float n=360/nr;
	int iter;
	int ancho=nr;
	int alto;
	bool tiene_tapa1=false;
	bool tiene_tapa2=false;
	vector<int> cub2;
	

	//Detecto si hay tapa encima y si la hay la quito antes de las revoluciones
	if(v1.at(0)<0.0001 && v1.at(2)<0.0001){
		aux.push_back(v1.at(0));
		aux.push_back(v1.at(1));
		aux.push_back(v1.at(2));
		v1.erase(v1.begin());
		v1.erase(v1.begin());
		v1.erase(v1.begin());
		tiene_tapa1=true;
	}
	//Hago igual para la tapa de abajo
	if(v1.at(v1.size()-3)<0.0001 && v1.at(v1.size()-1)<0.0001){
		aux2.push_back(v1.at(v1.size()-3));
		aux2.push_back(v1.at(v1.size()-2));
		aux2.push_back(v1.at(v1.size()-1));
		v1.pop_back();
		v1.pop_back();
		v1.pop_back();
		tiene_tapa1=true;
	}
	
	iter=v1.size();
	alto=iter/3;
	//Calculo los puntos para el ángulo n 
	for(int  i=n ; i<360 ; i+=n){
		for(int j=0 ; j<iter/3 ; j++ ){
			v1.push_back(v1[(j*3)]*cos((i*PI)/180));//transformo a radianes
			v1.push_back(v1[(j*3)+1]);
			v1.push_back(v1[(j*3)]*sin((i*PI)/180));
		}
	}


	//Genero la cara lateral formada por la rotación
	for(int p = 0;p < (ancho*alto); p++){
		if(contador<alto-1){
			c1.push_back(p);
			c1.push_back((p+alto)%(ancho*alto));
			c1.push_back((p+alto+1)%(ancho*alto));
			c1.push_back(p);
			c1.push_back((p+alto+1)%(ancho*alto));
			c1.push_back((p+1)%(ancho*alto));			
			contador++;		
		}
		else
			contador=0;
	}
	

	//Genero la cubierta poniendo un punto si en el perfil la cubierta no está incluida


	if(!tiene_tapa2){
		v1.push_back(0.0);
		v1.push_back(v1.at(v1.size()-3));
		v1.push_back(0.0);
	}
	else{
		v1.push_back(aux2.at(0));
		v1.push_back(aux2.at(1));
		v1.push_back(aux2.at(2));
	}
	if(!tiene_tapa1){
		v1.push_back(0.0);
		v1.push_back(v1.at(1));
		v1.push_back(0.0);
	}
	else{
		v1.push_back(aux.at(0));
		v1.push_back(aux.at(1));
		v1.push_back(aux.at(2));
	}

	
	//Uno los puntos con su respectiva tapadera		
	for(int r=0;r<alto*ancho;r+=alto){
		cub2.push_back((v1.size()/3)-1);	
		cub2.push_back((r+alto)%(alto*ancho));
		cub2.push_back(r);
		cub2.push_back(r+(alto-1));		
		cub2.push_back((r+(alto-1)+alto)%(alto*ancho));
		cub2.push_back((v1.size()/3)-2);			

	}
	
	Insertar(v1,c1);
	setCCubiertas(cub2);
}


