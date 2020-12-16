/*EJERCICIO 42:

El proveedor de repuestos de CosmeFulanito informó que una partida de repuestos salió con falla y debe ser devuelta.
 Para identificar la partida, el proveedor indicó que la falla fue en el partNumber: 1234 que tiene números de serie con el bit 3 y 5 en 1.

Para estas tareas se solicita:

    Hacer una cola con todos los registros fallados
    Realizar la baja física a todos los repuestos fallados
    Crear un archivo donde se vuelque el contenido de la cola en orden inverso.
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

struct cola{
	repuestos_t repuestos;
	struct cola *l;
};

void Encolar(struct cola *,struct cola *,repuestos_t rep);

int main(){
	struct cola *p=NULL, *u=NULL;
	repuestos_t rep;
	Encolar(p,u,rep);
	return 0;
}

void Encolar(struct cola *p,struct cola *u, repuestos_t rep){
	repuestos_t rep1;
	struct cola *aux = (struct cola*)malloc(sizeof(struct cola));
	FILE *rf, *rp, *rf1;
	if((rp=fopen("stock.txt","rt+"))==NULL){
		printf("No se encontro el archivo");
	}
	if((rf=fopen("stock1.txt","rt+"))==NULL){
		printf("No se encontro el archivo");
	}
	if((rf1=fopen("stock2.txt","rt+"))==NULL){
		printf("No se encontro el archivo");
	}
   	fread(&rep,sizeof(repuestos_t),1,rp);
    while(!feof(rp)){
      if(rep.partNumber & (1<<5) && rep.partNumber & (1<<3)){
      	rep1.partNumber=aux->repuestos.partNumber;
      	rep1.serialNumber=aux->repuestos.serialNumber;
      	strcpy(rep1.descripcion,aux->repuestos.descripcion);
	    strcpy(rep1.ubicacion,aux->repuestos.ubicacion);
		if(p==NULL){
	    	p=u=NULL;
		    aux->l=NULL;
	    }
	    else{
	    	u->l=aux;
	    	aux->l=NULL;
	    	u=aux;
	    }
	    fwrite(&rep,sizeof(repuestos_t),1,rf);
      }
   	fread(&rep,sizeof(repuestos_t),1,rp);
	}
	fclose(rp);
	fclose(rf);
	struct cola *aux1 = (struct cola*)malloc(sizeof(struct cola));
	aux1=u;
	while(aux1!=NULL){
		fwrite(&rep1,sizeof(repuestos_t),1,rf1);
		aux1=aux1->l;
	}	
	fclose(rf1);
}
