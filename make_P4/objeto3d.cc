/*
Santiago Vidal Martínez	
*/
#include "objeto3d.h"
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <jpeglib.h>
#include <file_ply_stl.h>

void Objeto3D::modificarSuavizado(){
	if(modo_suavizado==GL_SMOOTH){
		modo_suavizado=GL_FLAT;	
	}	
	else{
		modo_suavizado=GL_SMOOTH;
	}
	
	glShadeModel(modo_suavizado);
}



void Objeto3D::cambiarMaterialUsado(int n){
	n_material=n;
	if(n==0){
		for(int i=0;i<4;i++){
			mat_uso[i]=mat1_emision[i];
			mat_auso[i]=mat1_ambiente[i];
			mat_duso[i]=mat1_difuso[i];
			mat_euso[i]=mat1_especular[i];
		}
			brillouso=brillo;
    		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mat_uso);
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mat_auso);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_duso);
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,mat_euso);
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS,brillouso);
	}
	else if(n==1){
		for(int i=0;i<4;i++){
			mat_uso[i]=mat2_emision[i];
			mat_auso[i]=mat2_ambiente[i];
			mat_duso[i]=mat2_difuso[i];
			mat_euso[i]=mat2_especular[i];
			brillouso=brillo2;
		}
		brillouso=brillo2;
    		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mat_uso);
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mat_auso);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_duso);
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,mat_euso);
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS,brillouso);
	}
	else{
		for(int i=0;i<4;i++){
			mat_uso[i]=mat3_emision[i];
			mat_auso[i]=mat3_ambiente[i];
			mat_duso[i]=mat3_difuso[i];
			mat_euso[i]=mat3_especular[i];
		}
		brillouso=brillo3;
    		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mat_uso);
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mat_auso);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_duso);
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,mat_euso);
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS,brillouso);
	}
}

void Objeto3D::dibujar(char mode){
    		
     CalculoNormales();


	
     glEnable(GL_CULL_FACE);
     glEnableClientState( GL_COLOR_ARRAY ); 
     glEnableClientState( GL_NORMAL_ARRAY );
     glEnableClientState(GL_VERTEX_ARRAY);
/*     glEnable(GL_TEXTURE_2D);

     glEnableClientState( GL_TEXTURE_COORD_ARRAY );
      glTexCoordPointer( 2, GL_FLOAT, 0, &ctv[0]);*/ 	
      glVertexPointer(3, GL_FLOAT, 0, &v[0]);
     	CalculoNormales();			
	glNormalPointer(GL_FLOAT, 0, &normales_vertices[0]);
	glEnable(GL_NORMALIZE);	 
	//glShadeModel(GL_SMOOTH);
	 
	 //Modo de dibujado Sólido+Lineas+Puntos
	 if( mode == 'T' ){
	         glPolygonMode(GL_FRONT, GL_POINT);
		 glColorPointer(3,GL_FLOAT,0,&color_puntos[0]);		 
		 glDrawElements(GL_TRIANGLES,c.size(), GL_UNSIGNED_INT, &c[0]); 
	         glPolygonMode(GL_FRONT, GL_FILL);
		 glColorPointer(3,GL_FLOAT,0,&color_caras[0]);		 
		 glDrawElements(GL_TRIANGLES,c.size(), GL_UNSIGNED_INT, &c[0]); 
	         glPolygonMode(GL_FRONT, GL_LINE);
		 glColorPointer(3,GL_FLOAT,0,&color_lineas[0]);		 
		 glDrawElements(GL_TRIANGLES,c.size(), GL_UNSIGNED_INT, &c[0]); 	 
	 }

	 //Modo de dibujado de Ajedrez	
	 if( mode == 'A' ){
                glPolygonMode(GL_FRONT, GL_FILL);
		glColorPointer(3,GL_FLOAT,0,&color_ajedrez1[0]);		 
   	        glDrawElements(GL_TRIANGLES,c1.size(), GL_UNSIGNED_INT, &c1[0]); 
		glColorPointer(3,GL_FLOAT,0,&color_ajedrez2[0]);		 
   	        glDrawElements(GL_TRIANGLES,c2.size(), GL_UNSIGNED_INT, &c2[0]); 	 		
	 } 
	
	 //Modo de dibujado Sólido	 
	 if( mode == 'S' ){
                glPolygonMode(GL_FRONT, GL_FILL);
	 	glColorPointer(3,GL_FLOAT,0,&color_caras[0]); 	
	 }

	 //Modo de dibujado Lineas
 	 if( mode == 'L' ){
	 	glColorPointer(3,GL_FLOAT,0,&color_lineas[0]);
                glPolygonMode(GL_FRONT, GL_LINE);		
	 }

	 //Modo de dibujado Puntos	 	
	 if(mode=='P'){
	 	glColorPointer(3,GL_FLOAT,0,&color_puntos[0]);
	       	glPolygonMode(GL_FRONT, GL_POINT);		
	 }
	 
	 glDrawElements(GL_TRIANGLES,c.size(), GL_UNSIGNED_INT, &c[0]);      
     	 glDisableClientState(GL_VERTEX_ARRAY);	
     	 glDisableClientState(GL_NORMAL_ARRAY);	
	//glDisableClientState( GL_TEXTURE_COORD_ARRAY );

}

void Objeto3D::actualizarColores(){
	int num_cara=0;
	c2.clear();
	c1.clear();
	color_ajedrez1.clear();
	color_ajedrez2.clear();
	//Divido el vector en pares e impares para generar el color del modo ajedrez
	for( int j = 0; j < c.size(); j+=3 ){
		if( num_cara % 2 == 0){
			num_cara++;	
			c2.push_back(c.at(j));
			c2.push_back(c.at(j+1));
			c2.push_back(c.at(j+2));	
		}
		else{
			c1.push_back(c.at(j));	
			c1.push_back(c.at(j+1));
			c1.push_back(c.at(j+2));
			num_cara++;
		}	
     	}

	for( int p = 0; p < c1.size(); p++){
		color_ajedrez1.push_back(0.0);
		color_ajedrez1.push_back(0.0);
		color_ajedrez1.push_back(0.0);		
	}

	for( int r = 0; r < c1.size(); r++){
		color_ajedrez2.push_back(1.0);
		color_ajedrez2.push_back(0.0);
		color_ajedrez2.push_back(0.0);	
	}	
}


void Objeto3D::CalculoNormales(){
	
 float px,py,pz,qx,qy,qz,rx,ry,rz,ax,ay,az,bx,by,bz,ncx,ncy,ncz,nvx,nvy,nvz;
 float modc, modv;

 normales_vertices.clear();
 normales_caras.clear();


 for(int i=0;i<v.size();i++){
  normales_vertices.push_back(0.0);
 }

 //cout<<"Tama normales vertices:"<<normales_vertices.size()<<endl;
 //Calculamos las normales de caras
 for(int j=0;j<c.size();j+=3){

  px=v[c[j]*3];
  py=v[c[j]*3+1];
  pz=v[c[j]*3+2];
  qx=v[c[j+1]*3];
  qy=v[c[j+1]*3+1];
  qz=v[c[j+1]*3+2];
  rx=v[c[j+2]*3];
  ry=v[c[j+2]*3+1];
  rz=v[c[j+2]*3+2];

  ax=qx-px;
  ay=qy-py;
  az=qz-pz;	

  bx=rx-px;
  by=ry-py;
  bz=rz-pz;
  //Hacemos el producto vectorial

  	ncx = (ay*bz - by*az);
  	ncy = (-1)*(ax*bz - bx*az);
  	ncz = (ax*by - bx*ay);	
	
  //Normalizamos
  modc = sqrt(pow(ncx,2)+pow(ncy,2)+pow(ncz,2));
  if(modc != 0){
   ncx /= modc;
   ncy /= modc;
   ncz /= modc;
  }
  normales_caras.push_back(ncx);
  normales_caras.push_back(ncy);
  normales_caras.push_back(ncz);


  //Vamos calculando las normales de vértices
  normales_vertices[c[j]*3] += ncx;
  normales_vertices[c[j]*3+1] += ncy;
  normales_vertices[c[j]*3+2] += ncz;

  normales_vertices[c[j+1]*3] += ncx;
  normales_vertices[c[j+1]*3+1] += ncy;
  normales_vertices[c[j+1]*3+2] += ncz;

  normales_vertices[c[j+2]*3] += ncx;
  normales_vertices[c[j+2]*3+1] += ncy;
  normales_vertices[c[j+2]*3+2] += ncz;
 
 }

 //Normalizamos las normales de vértices
 for(int i=0; i < normales_vertices.size(); i+=3){
  modv = sqrt(pow(normales_vertices[i],2)+pow(normales_vertices[i+1],2)+pow(normales_vertices[i+2],2));
  
  if(modv != 0){
   normales_vertices[i] /= modv;
   normales_vertices[i+1] /= modv;
   normales_vertices[i+2] /= modv;
  }


 }


}

void Objeto3D::Insertar(vector<float> v1,vector<int> cp){

	v=v1;
	c=cp;
	v2=v1;	
	conex2=c;
	int tama1=((c.size()/3)/2)*3; 
	
	if(normales_vertices.size()==0)
		CalculoNormales();
	//Inserto los colores
     	for( int i = 0; i < c.size(); i++ ){
		color_caras.push_back(1.0);
		color_caras.push_back(0.0);
		color_caras.push_back(0.0);
		color_lineas.push_back(0.0);
		color_lineas.push_back(0.0);
		color_lineas.push_back(0.0);
		color_puntos.push_back(0.0);
		color_puntos.push_back(1.0);
		color_puntos.push_back(0.0);	
     	}
	
	actualizarColores();
			
}


void Objeto3D::cargarPLY(string ply){
  reiniciar();	
  _file_ply File_ply;
  vector<_vertex3f> Vertices;
  vector<_vertex3i> Triangles;
  vector<float> vertices;
  vector<int> caras;
		
  if ( File_ply.open(ply) ){
    
	File_ply.read(Vertices,Triangles);
	std::cout << "File read correctly" << std::endl;
  
  	for( int i = 0; i < Vertices.size(); i++){
		vertices.push_back(Vertices.at(i)._0);
  		vertices.push_back(Vertices.at(i)._1);
  		vertices.push_back(Vertices.at(i)._2);	 
    	}
  
	for( int j = 0; j < Triangles.size(); j++){
		caras.push_back(Triangles.at(j)._0);
  		caras.push_back(Triangles.at(j)._1);
  		caras.push_back(Triangles.at(j)._2);	 
    	}		

    Insertar(vertices,caras);	  

  }

  else std::cout << "File can't be opened" << std::endl;

}

/*
El siguiente modo detecta si las tapas están activas o no y las pone o las quita	
*/
void Objeto3D::poner_quitar_cubiertas(){
	
	int num_cara=0;
	if( tapa_activa ){
		
		tapa_activa=false;		
		for( int i = 0; i < cubiertas.size(); i++)
			v.pop_back();

		for( int j = 0; j < c_cubiertas.size(); j++)
			c.pop_back();
			
		
	}

	else{
		for( int i = 0; i < cubiertas.size(); i++)
			v.push_back(cubiertas.at(i));

		for( int j = 0; j < c_cubiertas.size(); j++)
			c.push_back(c_cubiertas.at(j));

		tapa_activa=true;

			
	}

	actualizarColores();
			
}

/*
Invierte el orden de los puntos de las figuras
*/
void Objeto3D::invertirPuntos(){

	vector<float> aux;

	for( int i = v.size()-1; i >= 0; i -= 3){
		aux.push_back(v.at(i-2));
		aux.push_back(v.at(i-1));
		aux.push_back(v.at(i));			
	}

	v.clear();
	v=aux;
}

void Objeto3D::reiniciar(){
	v.clear();
	v2.clear();
	c.clear();
	conex2.clear();
	c1.clear();
	c2.clear();
	cubiertas.clear();
	c_cubiertas.clear();
	color_caras.clear();
	color_puntos.clear();
	color_lineas.clear();
	color_ajedrez1.clear();
	color_ajedrez2.clear();
	tapa_activa=false;		
}















