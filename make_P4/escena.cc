/*
Santiago Vidal Martínez	
*/
#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "escena.h"
//#include "objeto3d.h"
#include "cubo.h"
#include "tablero.h"
#include "tetraedro.h"
#include "piramide.h"
#include "esfera.h"
#include "octaedro.h"
#include "objetoply.h"
#include "objetorevolucion.h"
#include "objeto_jerarquico.h"
#include <string>
#include <cmath>

Escena::Escena(){
    Front_plane=50;
    Back_plane=2000;
    Observer_distance = 4*Front_plane;
    Observer_angle_x = Observer_angle_y=0;
    ejes.changeAxisSize(5000);

    Tetraedro o(30.0);	
    Cubo c(30.0);
    Piramide r(30.0);
    Octaedro oc(30.0);
    Tablero t(16);
    tablero=t;
    
    v.push_back(o);
    v.push_back(c);
    v.push_back(r);
    v.push_back(oc);
    Objeto_jerarquico nuevo(rot,rot2,a,cuello);
    
    float ambiental[4]={1.0,1.0,1.0,0.0};
    float especular[4]={1.0,1.0,1.0,1.0};
    float difusa[4]={1.0,1.0,1.0,1.0};

    lucecita.crearLuz(l1,l2,l3,GL_LIGHT2,&ambiental[0],&especular[0],&difusa[0],0.0);
    lucecita2.crearLuz(p1,p2,p3,GL_LIGHT3,&ambiental[0],&especular[0],&difusa[0],1.0);
//    lucecita2.crearLuz(0.0,0.0,0.0,GL_LIGHT3);
    mario=nuevo;

}

void Escena::inicializar(int UI_window_width,int UI_window_height) {

	glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer


	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);

}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects() {

	glPointSize(5.0f);    
	string fich;


	/*
	Hasta la línea 89 de este código actualiza los atributos de estado para
	posteriormente pintar el objeto
	*/
		
	if (tecla == 'I'){
		if(!luz_activa){

			lucecita.activar();
			lucecita2.activar();
			luz_activa=true;
			tecla=' ';
		}
		else{
			lucecita.desactivar();
			lucecita2.desactivar();
			luz_activa=false;
			tecla=' ';
			//glDisable(GL_LIGTHING);
			//glDisable(GL_LIGTH0);
		}
	}
	if(tecla=='H'){
		tecla=' ';

		if(textura){
			textura=false;	
		}
		else{
			textura=true;
		}
	}

	if (tecla == 'Y'){
		cambio_suavizado=true;
		tecla=' ';
	}
		
	if ( tecla == '1' ){
		objeto_activo = (objeto_activo + 1) % 4;
		tipo_obj = '1';	
	}

	else if (tecla=='b'){
		if(b3>=0.0)
			b3-=0.1;
		tecla='4';
	}
	else if (tecla=='B'){
		if(b3<=1.5) 	
			b3+=0.1;
		tecla='4';
	}
	else if (tecla=='v'){
		if(b2>0.0)
			b2-=0.1;
		if(b3>=0.0)
			b3-=0.1;
		if(b1>0.00001)
			b1-=0.1;
		tecla='4';	
	}
	else if (tecla=='V'){
		if(b2<1.5) 
			b2+=0.1;
		if(b3<=1.5) 	
			b3+=0.1;
		if(b1<1.5) 
			b1+=0.1;
		tecla='4';
	}
	else if (tecla=='m'){
		if(b2>0.0)
			b2-=0.1;
			//cout<<b2<<endl;
		tecla='4';	
	}
	else if (tecla=='M'){
		if(b2<1.5) 
		b2+=0.1;
//		cout<<b1<<endl;
		tecla='4'; 	
	}
	else if (tecla=='n'){
		if(b1>0.00001)
			b1-=0.1;
//			cout<<b1<<endl;
		tecla='4';		
	}
	else if (tecla=='N'){
		if(b1<1.5) 
		b1+=0.1;
//		cout<<b1<<endl;
		tecla='4'; 	
	}
	else if (tecla=='z'){
		if(a<25)	 
			a=a+1.0;
		//cout<<tecla<<endl;
		tecla='4';
	}
	else if (tecla=='Z'){ 
		if(a>0)		
			a=a-1.0;
		tecla='4';	
	}
	else if (tecla=='X'){ 
		if(rot<18+rot2)
		rot=rot+1.0;
		tecla='4';
	}
	else if (tecla=='x'){ 
		if(rot>-25+rot2)
			rot=rot-1.0;
		tecla='4';	
	}
	else if (tecla=='C'){
		if(rot2<20+(rot+10) && rot2<40)	 
			rot2=rot2+1.0;
		tecla='4';	
	}
	else if (tecla=='c'){
		if(rot2>=-18+(rot+10) && rot2>=-18)	
			rot2=rot2-1.0;		
		tecla='4';
	}
	else if ( tecla == '2' ){
		tipo_obj = '2';
		esta = true;
	}

	else if( tecla == '3' ){
		tipo_obj = '3';
		esta2 = true;
		esta_cargado=false;
	}
	else if ( tecla == '4' ){
		tipo_obj = '4';
		esta = true;
	}
	else if ( tecla == '5' ){
		tipo_obj = '5';
		esta = true;
	}

	else if( tecla == '+' ){
		segmentos++;
		tipo_obj = '3';
		esta2 = true;
	}

	else if( tecla == '-' ){
		if(segmentos>2)
			segmentos--;

		tipo_obj = '3';
		esta2 = true;
	}
	else if( tecla == 'P' ) modo_activo = 'P';
	else if( tecla == 'L' ) modo_activo = 'L';
	else if( tecla == 'S' ) modo_activo = 'S';
	else if( tecla == 'A' ) modo_activo = 'A';
	else if( tecla == 'T' ) modo_activo = 'T';
	else{
		esta = false;
		esta2 = false;	
	}	

	/*
	Dependiendo del tipo de objeto activo se pinta uno u otro: tipo 1 
	(objetos3D), tipo 2 (objetosPLY) y tipo 3 (objetosRevolucion)	
	*/
	if(tipo_obj=='1'){
		v.at(objeto_activo).cambiarMaterialUsado(material_activo);
		if(cambio_suavizado){
			cambio_suavizado=false;			
			v.at(objeto_activo).modificarSuavizado();
		}
		v.at(objeto_activo).dibujar(modo_activo);
	}

	if(tipo_obj=='2'){
		if(esta==true){
			cout<<"Introduzca el nombre del fichero ply: ";		
			cin>>objeto1;
			objeto1="objetosPLY/"+objeto1;
			esta=false;
		}
		q.cargarPLY(objeto1);
		q.cambiarMaterialUsado(material_activo);
		if(cambio_suavizado){
			cambio_suavizado=false;			
			q.modificarSuavizado();
		}	
		q.dibujar(modo_activo);
	}
	if(tipo_obj=='3'){
		if(esta2==true){
			if(!esta_cargado){
				char c2;
				float punto;

				cout<<"¿Quiere cargarlo de un ply?(y/n)"<<endl;
				cin>>c2;
				if(c2=='y'){
					cout<<"Introduzca el nombre del fichero ply:";		
					cin>>objeto2;
					objeto2="objetosRevolucion/"+objeto2;
				}
				else{
					/*cout<<"Introduzca puntos (x,y,z) (Finalizar -1.0)"<<endl;
					while(punto!=-1.0 || c.size()%3!=0 || c.size()<3){
						cin>>punto;
						if(punto!=-1.0 || c.size()%3!=0)
							c.push_back(punto);
						cout<<"Introduzca puntos (x,y,z) (Finalizar -1.0)"<<endl;	
					}*/
					
					vector<float> aux ={3.0,5.0,0.0,3.0,4.0,0.0,3.0,3.0,0.0,2.0,2.0,0.0,1.5,1.0,0.0,1.0,0.0,0.0};
					c=aux;	

				}
			}
			p.crearObjeto(objeto2,segmentos,c);
			esta2=false;
			esta_cargado=true;
		}
		//Esto indica si ponemos o quitamos las cubiertas
		if(tecla=='*') 
			p.poner_quitar_cubiertas();		
		
		p.cambiarMaterialUsado(material_activo);
		if(cambio_suavizado){
			cambio_suavizado=false;			
			p.modificarSuavizado();
		}
		p.dibujar(modo_activo);	

	}
	if ( tipo_obj == '4' ){
	
		mario.asignar(rot,rot2,a,cuello);
		mario.cambiarMaterialUsado(material_activo);
		if(cambio_suavizado){
			cambio_suavizado=false;			
			mario.modificarSuavizado();
		}
		mario.pintar(modo_activo);

		//glutIdleFunc(idle);
	}
	if ( tipo_obj == '5' ){
		
		
		tablero.cambiarMaterialUsado(material_activo);
		if(cambio_suavizado){
			cambio_suavizado=false;			
			tablero.modificarSuavizado();
		}
		tablero.setActivo(textura);
		tablero.Textura();
		tablero.dibujar(modo_activo);

		//glutIdleFunc(idle);
	}

	
	
}

		
void Escena::dibujar() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	draw_axis();
	draw_objects();
}

int Escena::teclaPulsada(unsigned char Tecla1,int x,int y) {

    std::cout << "Tecla" << Tecla1<< std::endl;
	if(Tecla1!='z' && Tecla1!='x' && Tecla1!='c' && Tecla1!='b' && Tecla1!='n' && Tecla1!='m' && Tecla1!='v')	
		tecla=toupper(Tecla1);
	else
		tecla=Tecla1;
	if (toupper(Tecla1)=='Q') return 1;
	else return 0;
}

void Escena::modifica(){
	
	if(a>25){ 
		yoyoabajo=true;
		yoyoarriba=false;
	}		
	if(a<0){ 
		yoyoabajo=false;
		yoyoarriba=true;
	}
	if(cuello>15.0){
		//cout<<cuello<<endl; 
		cuello_arriba=true;
		cuello_abajo=false;
	}	
	if(cuello<-0.00001){ 
		//cout<<cuello<<endl; 
		cuello_arriba=false;
		cuello_abajo=true;
	}		
	if(a<0){ 
		yoyoabajo=false;
		yoyoarriba=true;
	}
	if(rot>18.0+rot2){ 
		mano_abajo=false;
		mano_arriba=true;
	}		
	if(rot<-25.0+rot2){ 
		mano_abajo=true;
		mano_arriba=false;
	}
	
	if(rot2>20){ 
		brazo_abajo=true;
		brazo_arriba=false;
	}		
	if(rot2<-8){ 
		brazo_abajo=false;
		brazo_arriba=true;
	}		
	if(mano_arriba){
		rot-=b1;
//			if(a>-2)
//				a-=b3/1.5;	
	}
	if(mano_abajo){
//			if(a<20.0)
//				a+=b3;	
		rot+=b1;
	}
	if(brazo_arriba){
		rot2+=b2;

	}
	if(brazo_abajo){
		rot2-=b2;
	}
	if(yoyoarriba){
		a+=b3;
	}
	if(yoyoabajo){
		a-=b3;
	}
	if(cuello_arriba){
		cuello-=b4;
	}
	if(cuello_abajo){
		cuello+=b4;
	}

}


void Escena::teclaEspecial(int Tecla1,int x,int y) {
	tecla=Tecla1;
	cout<<tecla<<endl;
switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F5:material_activo=0;break;
	case GLUT_KEY_F6:material_activo=1;break;
	case GLUT_KEY_F7:material_activo=2;break;
	case GLUT_KEY_F1:cambiarPosLuz1();break;
	case GLUT_KEY_F2:cambiarPosLuz2();break;				
	
	}

	std::cout << Observer_distance << std::endl;
}


void Escena::cambiarPosLuz1(){
	if(pos==0){
		l1=lx;
		l2=ly;
		l3=lz;		
	}
	else if(pos==1){
		l1=lx1;
		l2=ly1;
		l3=lz1;
	}
	else if(pos==2){
		l1=lx2;
		l2=ly2;
		l3=lz2;
	}
	else{
		l1=lx3;
		l2=ly3;
		l3=lz3;
	}
	pos=(pos+1)%4;
	lucecita.desactivar();
	lucecita.setPosicion(l1,l2,l3);	
	lucecita.activar();
}

void Escena::cambiarPosLuz2(){
	if(pos2==0){
		p1=px;
		p2=py;
		p3=pz;		
	}
	else if(pos2==1){
		p1=px1;
		p2=py1;
		p3=pz1;
	}
	else if(pos2==2){
		p1=px2;
		p2=py2;
		p3=pz2;
	}
	else{
		p1=px3;
		p2=py3;
		p3=pz3;
	}
	pos2=(pos2+1)%4;
	lucecita2.desactivar();
	lucecita2.setPosicion(p1,p2,p3);	
	lucecita2.activar();
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void Escena::change_projection()  {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Width/aumento,Width/aumento,-Height/aumento,Height/aumento,Front_plane,Back_plane);
}


void Escena::redimensionar(int newWidth,int newHeight) {
change_projection();
Width=newWidth;
Height=newHeight;
glViewport(0,0,newWidth,newHeight);
}


//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************



void Escena::change_observer() {

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis()
{
ejes.draw();
}




