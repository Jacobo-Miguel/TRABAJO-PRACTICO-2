/*EJERCICIO 43:

El servicio técnico de CosmeFulanito recibe órdenes de trabajo diarias. 
Las mismas son cargadas en un archivo secuencial por el personal de recepción bajo la siguiente estructura de datos:

typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

Se pide:
    Hacer una pila con las órdenes de trabajo de forma tal que la más vieja sea la última en cargarse.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

struct pila{
	repuestos_t repuestos;
	struct pila *l;
};

struct pila * Apilar(struct pila *,repuestos_t rep);
int main(){
	repuestos_t rep;
	struct pila *p=NULL;
	p=Apilar(p,rep);
	return 0;
}

struct pila * Apilar(struct pila *p,repuestos_t rep){
	FILE *repuesto;
	if((repuesto=fopen("repuesto.txt","rt+"))==NULL){
		printf("No se pudo encontrar el archivo");
	}
	
	fread(&rep,sizeof(rep),1,repuesto);
	while(!feof(repuesto)){
		struct pila *aux=(struct pila *)malloc(sizeof(struct pila));
	
	    aux->repuestos.numeroDeOrden=rep.numeroDeOrden;
     	strcpy(aux->repuestos.cliente,rep.cliente);
    	strcpy(aux->repuestos.descripciondeFalla,rep.descripciondeFalla);
    	strcpy(aux->repuestos.modelo,rep.modelo);
    	strcpy(aux->repuestos.fecha,rep.fecha);
    	strcpy(aux->repuestos.hora,rep.hora);
	
     	if(p==NULL){
	    	p=aux;
	        aux->l=NULL;
	    }
	    else{
	    	aux->l=p;
	    	p=aux;
    	}
    fread(&rep,sizeof(rep),1,repuesto);	
	}
	fclose(repuesto);
	return p;
}