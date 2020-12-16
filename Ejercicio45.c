/*EJERCICIO 45:

La lista creada en el ejercicio 44 es procesada por el depósito. Para dicha tarea se pide hacer un programa que:

    Descuente las cantidades solicitadas del archivo de stock, creado en el Ejercicio 41.
    Hacer una cola con los repuestos en los que no se encontró stock suficiente para poder notificar a los clientes la demora de la reparación.*/
    
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
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
}repuestos_t1;


typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;

struct lista{
    extraccionRepuestos_t ext;
	struct lista *l;	
};

struct cola{
	repuestos_t1 repuestos;
	struct cola *l;
};

void crearCola(struct cola *,struct cola *,repuestos_t1 rep1);

int main(){
	struct cola *p=NULL, *u=NULL;
	repuestos_t rep;
	repuestos_t1 rep1;
	crearCola(p,u,rep1);
	return 0;
}

void crearCola(struct cola *p,struct cola *u,repuestos_t1 rep1){
	struct lista *naux=(struct lista*)malloc(sizeof(struct lista));
	struct cola *aux=(struct cola*)malloc(sizeof(struct cola));
	FILE *rp;
	long clave,clave2;
	if((rp=fopen("stock.txt","rt+"))==NULL){
		printf("No se encontro el archivo ");
	}
	fread(&rep1,sizeof(repuestos_t),1,rp);
	printf("Ingrese el PartNumber: ");
	scanf("%l",&clave);
	while(!feof(rp)){
		if(clave==rep1.partNumber){
			printf("Ingrese el SerialNumber: ");
			scanf("%l",&clave2);
			if(clave2=rep1.serialNumber){
				naux->ext.cantidad=naux->ext.cantidad-1;
			}
			if(rep1.serialNumber==NULL){
				aux->repuestos.partNumber = rep1.partNumber;
             	aux->repuestos.serialNumber = rep1.serialNumber;
            	strcpy(aux->repuestos.descripcion,rep1.descripcion);
            	strcpy(aux->repuestos.ubicacion,rep1.ubicacion);
				if(p==NULL){
	             	p=u=NULL;
		            aux->l=NULL;
	            }
	            else{
	             	u->l=aux;
	            	aux->l=NULL;
	            	u=aux;
	            }
			}
		}
		fread(&rep1,sizeof(repuestos_t),1,rp);	
	}
}
