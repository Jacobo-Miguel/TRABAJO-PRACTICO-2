/*EJERCICIO 39:

Hacer un programa que tome los datos de medición de potencia, cargados por el usuario, de un sistema de medición a distancia.
Los datos que cargará el usuario tienen la siguiente estructura:

    char desc[60];
    unsigned char potencia;
    unsigned int estado;

Donde estado es la multiplicación del valor ASCII de la primer letra de la descripción por la potencia. 
Los datos cargados se deberán guardar en una lista ordenada, de mayor a menor, del valor de potencia. 
Una vez finalizada la carga guardar los datos en un archivo de organización directa llamado "potencia.dat" imprimiendo en pantalla los datos.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct datos{
	char desc[60];
	unsigned char potencia;
	unsigned int estado;
	int id;
}datos_t;

typedef struct lista{
     datos_t datos;
     struct lista *siguiente;
     struct lista *anterior;
}lista_t;


int main(){
	char op;
	int dato=1;
	FILE * potencia;
	datos_t datos;
	lista_t *primero, *ultimo, *r;
	primero=ultimo=NULL;
	do{
	lista_t *nuevo = (lista_t*)malloc(sizeof(lista_t));
	printf("Ingrese la descripcion: ");
	scanf("%s",&nuevo->datos.desc);
	printf("La letra %c es %d en codigo ASCII",nuevo->datos.desc[0],nuevo->datos.desc[0]);
	printf("\nIngrese la potencia: ");
	scanf("%d",&nuevo->datos.potencia);
	nuevo->datos.estado = (nuevo->datos.desc[0]*nuevo->datos.potencia);
	printf("El estado es: %d",nuevo->datos.estado);
	
	if(primero==NULL){
		primero=ultimo=nuevo;
		ultimo->siguiente=NULL;
	}
	else{
		r=primero;
		while(1){
			if(r->datos.potencia < nuevo->datos.potencia){
				nuevo->siguiente = primero;
				primero = nuevo;
				break;
			}
			while(r->siguiente!=NULL){
				if(r->siguiente->datos.potencia > nuevo->datos.potencia){
					r = r->siguiente;
				}
			}
			if(r==ultimo){
				ultimo->siguiente = nuevo;
				ultimo = nuevo;
				ultimo->siguiente = NULL;
				break;
			}
			nuevo->siguiente = r->siguiente;
			r->siguiente = nuevo;
			break;
		}
	}
	
	fflush(stdin);
	printf("\nAGREGAR OTRA MEDICION: ");
	scanf("%c",&op);
	}while((op=='S')||(op=='s'));
	if((potencia=fopen("potencia.dat","wb"))==NULL){
		printf("No se pudo crear el archivo");
	}
	else{
		lista_t *actual = (lista_t*)malloc(sizeof(lista_t));
	    actual = primero;
	    if(actual != NULL){
	    	while(actual != NULL){
	    		actual->datos.id = dato;
	            dato++;
		    	fwrite(&actual->datos,sizeof(actual->datos),1,potencia);
		    	actual = actual->siguiente;
	    	}
	    }
	    else{
	    	printf("LA LISTA ESTA VACIA\n");
     	}
	}
	fclose(potencia);
	if((potencia=fopen("potencia.dat","rb"))==NULL){
		printf("No se pudo crear el archivo");
	}
	else{
		fread(&datos,sizeof(datos),1,potencia);
		printf("LISTA DE DATOS EN EL ARCHIVO POTENCIA.DAT\n");
		printf("ID  |  DESCRIPCION  |  POTENCIA  |  ESTADO");
		while(!feof(potencia)){
			printf("\n%d   |  %s         |     %d      |     %d",datos.id,datos.desc,datos.potencia,datos.estado);
			fread(&datos,sizeof(datos),1,potencia);
		}
	}
	fclose(potencia);
	return 0;
}
