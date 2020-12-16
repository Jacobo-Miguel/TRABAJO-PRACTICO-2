/*EJERCICIO 41:

El depósito de la empresa CosmeFulanito necesita cargar su stock de repuestos en forma ordenada. 
Para dicha tarea se solicitó categorizar a los respuestos bajo la siguiente estructura de datos:

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
}repuestos_t;

Los repuestos no están ordenados, se solicita cargarlos en una lista, la cual ordene por descripción
 a los repuestos para luego guardarlos en un archivo de stock con organización secuencial.

        Imprimir en pantalla la lista con cada inserción.
        El archivo se generará cuando el usuario decide no cargar mas productos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
}repuestos_t;

struct lista{
	repuestos_t repuestos;
	struct lista *l;
};

repuestos_t repuestos(repuestos_t repuestos);
struct lista * Listar(struct lista * , struct lista * ,repuestos_t repuestos);
void MostrarLista(struct lista *);

int main(){
	struct lista *p=NULL, *u=NULL, *naux;
	repuestos_t rep;
	FILE *rp;
	char opc;
	do{
		rep = repuestos(rep);
		naux = Listar(p , u ,rep);
		MostrarLista(p);
		printf("Desea agregar mas repuestos? (S/N): ");
		scanf("%c",&opc);
	}while(opc!='n'&& opc!='N');
	
	if((rp=fopen("stock.txt","rt+"))==NULL){
		printf("No se encontro el archivo");
	}
	fwrite(&rep,sizeof(repuestos_t),1,rp);
	fclose(rp);
	return 0;
}

repuestos_t repuestos(repuestos_t repuestos){ // funcion para ingresar los datos
    	printf("Cargar los repuestos\n\n");
		printf("PartNumber: ");
		scanf("%l",&repuestos.partNumber);
		fflush(stdin);
		printf("SerialNumber: ");
		scanf("%l",&repuestos.serialNumber);
		fflush(stdin);
		printf("Descripcion: ");
		gets(repuestos.descripcion);
		fflush(stdin);
		printf("Ubicacion: ");
		gets(repuestos.ubicacion);
		fflush(stdin);
		
		return repuestos;
}

struct lista* Listar(struct lista *p,struct lista *u ,repuestos_t repuestos){ //funcion para crear la lista
	struct lista *aux, *r;
	
	aux = (struct lista * )malloc(sizeof(struct lista));
	r=p;
	aux->repuestos.partNumber = repuestos.partNumber;
	aux->repuestos.serialNumber = repuestos.serialNumber;
	strcpy(aux->repuestos.descripcion,repuestos.descripcion);
	strcpy(aux->repuestos.ubicacion,repuestos.ubicacion);
	
	if(p==NULL){
		p=u=aux;
		u->l=NULL;
	}
	
	if(r->repuestos.descripcion > aux->repuestos.descripcion && r->l && r==u){
		if(r->repuestos.descripcion > aux->repuestos.descripcion){
		aux->l = p;
		p = aux;
	   }
	
      while(r->l){
		if(r->l->repuestos.descripcion < aux->repuestos.descripcion){
			r = r->l;
		}
      }
	
	  if(r==u){
		u->l = aux;
		u=aux;
		u->l=NULL;
	  }
	}
	
	aux->l=r->l;
    r->l=aux;
    
    return aux;
}

void MostrarLista(struct lista *p){  //funcion para mostrar la lista
	struct lista *naux =  (struct lista *)malloc(sizeof(struct lista));
	naux = p;
	
	while(naux!=NULL){
		printf("%l//%l//%s//%s\n",naux->repuestos.partNumber,naux->repuestos.serialNumber,naux->repuestos.descripcion,naux->repuestos.ubicacion);
		naux = naux->l;
	}
}

