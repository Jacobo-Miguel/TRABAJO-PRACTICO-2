/*EJERCICIO 44:

El servicio técnico utiliza la pila generada en el ejercicio 43 en su labor diaria. 
Cada técnico toma una tarea de la pila y genera un orden de extracción de repuestos al depósito. 
Para optimizar los viajes al depósito se arma una lista con los repuestos que cada orden necesita utilizando la siguiente estructura:

typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;

Se pide cargar la lista de repuestos solicitados por los técnicos. 
Tener en cuenta que varios técnicos pueden necesitar la misma parte, y en esos casos se debe incrementar la cantidad pedida en la lista.*/

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

typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;

struct lista{
    extraccionRepuestos_t ext;
	struct lista *l;	
};

struct pila{
	repuestos_t repuestos;
	struct pila *l;
};

struct pila * Apilar(struct pila *,repuestos_t rep);
struct lista * crearLista(struct lista *,struct lista *);
int main(){
	repuestos_t rep;
	struct pila *p=NULL;
	struct lista *pri=NULL, *ult=NULL, *aux;
	
	p=Apilar(p,rep);
	aux=crearLista(pri,ult);
	return 0;
}

struct pila * Apilar(struct pila *p,repuestos_t rep){
	FILE *repuesto;
	if((repuesto=fopen("repuesto.txt","rt+"))==NULL){
		printf("No se pudo encontrar el archivo");
	}
	
	fread(&rep,sizeof(repuestos_t),1,repuesto);
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

struct lista * crearLista(struct lista *p,struct lista *u){
	struct lista *aux, *r;	
	aux = (struct lista * )malloc(sizeof(struct lista));
	printf("Ingrese la cantidad necesitada: ");
	scanf("%d",&aux->ext.cantidad);
	
	if(p==NULL){
		p=u=aux;
		u->l=NULL;
	}
	
	if(r->ext.cantidad > aux->ext.cantidad && r->l && r==u){
		if(r->ext.cantidad > aux->ext.cantidad){
		aux->l = p;
		p = aux;
	   }
	
      while(r->l){
		if(r->l->ext.cantidad < aux->ext.cantidad){
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
