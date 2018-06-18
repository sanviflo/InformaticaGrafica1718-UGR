/*
Santiago Vidal Martínez	
*/
#include "objeto3d.h"
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "tablero.h"
#include <fstream>
Tablero::Tablero(int longitud){
		
		vector<float> vertices;
		vector<int> caras;
		
		//cout<<"tamaño:"<<longitud<<endl;

		
		for(int i=-longitud/2;i<=longitud/2;i++){
			for(int j=-longitud/2;j<=longitud/2;j++){
				vertices.push_back(i);
				//cout<<i<<" "; 
				vertices.push_back(-j);
				//cout<<-j<<" ";
				vertices.push_back(0.0);
				//cout<<0.0<<endl;

			}
		}
		

		//int p=1;
		for(int p=0;p<longitud;p++){
			for(int j=0;j<longitud;j++){
				int q=j+p;
				caras.push_back(p*longitud+q);
				caras.push_back(p*longitud+1+q);
				caras.push_back(p*longitud+longitud+1+q);

				caras.push_back(p*longitud+longitud+1+q);
				caras.push_back(p*longitud+1+q);
				caras.push_back(p*longitud+longitud+2+q);
				/*caras.push_back(p*longitud+q);
				caras.push_back(p*longitud+1+q);	
				caras.push_back(p*longitud+longitud+2+q);*/
			}
		}
		
		Insertar(vertices,caras);

		float fila=1.0,col=0.0;
		float aumento = 1.0/longitud;
		
		for(int i=0;i<getSize()+1;i++){
			if(col>=1.0){
				ctv.push_back(col);
				ctv.push_back(fila);
				col=0.0;
				fila-=aumento;			
			}
			else{
				ctv.push_back(col);
				ctv.push_back(fila);
				col+=aumento;			
			}							
		}

		
	
}	

GLuint Tablero::LoadBMP(const char * imagepath) {
	
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	
	// Información RGB
	unsigned char * data;
	
	FILE * file = fopen(imagepath,"rb");
	if (!file){
		cout<<"La imagen no se pudo abrir con éxito\n"; 
		return 0;
	}
	
	if ( fread(header, 1, 54, file)!=54 ){
		cout<<"No tiene formato .bmp\n";
		return false;
	}
	
	if ( header[0]!='B' || header[1]!='M' ){
		cout<<"No tiene formato .bmp\n";
		return 0;
	}

	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	if (imageSize==0)    imageSize=width*height*3; 
	if (dataPos==0)      dataPos=54;
	
	data = new unsigned char [imageSize];

	fread(data,1,imageSize,file);
	fclose(file);
	
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}

void Tablero::Textura(){
	if(activado){
		idTex=LoadBMP("./image/textura.bmp");
		glEnable (GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D,idTex);
		glTexCoordPointer(2,GL_FLOAT,0,&ctv[0]);
	}
	else{
		glDisable (GL_TEXTURE_2D);
	}
}
	



