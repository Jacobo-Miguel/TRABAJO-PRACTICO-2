/*EJERCICIO 37:
Existe un archivo llamado "datos.dat", de tipo binario, cuya organización es secuencial. Los datos están organizados según la siguiente estructura:

struct d{                                                                                            
long clave; //Clave o Id del registro
char d[30]; // Descripcion                                                                                          
unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
char b; //'A':Alta 'B':Baja                                                                                                                                                                          
}
Se Pide: Realizar una funcion que pase como parámetro la clave, entre otros parámetros, y apile dos valores, la Clave y 
su posición física respecto al archivo (registro 1, 2, etc), si es que el campo tipo tiene el bit 4 con valor 1. 
En caso de no encontrarlo mostrar por pantalla "Registro no encontrado". La función debe devolver el puntero de pila. 
Realizar el main con varias llamadas a dicha función y proceder a mostrar las descripciones del archivo, mediante la pila como acceso directo, NO USAR VARIABLES GLOBALES.*/

#include <stdio.h>
#include <stdlib.h>

struct d{                                                                                            
long clave; //Clave o Id del registro
char d[30]; // Descripcion                                                                                          
unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
char b; //'A':Alta 'B':Baja                                                                                                                                                                          
};

typedef struct pila{
	struct d d;
	struct pila *siguiente;
}pila;
pila *armarpila(struct d aux,struct pila *inicio);

int main(){
	FILE * datos;
	char op;
	struct d aux;
    pila *inicio=NULL;
	if((datos=fopen("datos.dat","wb+"))==NULL){
		printf("\nNO SE PUDO LEER EL ARCHIVO");
	}
	else{
		do{
		printf("INGRESE LA CLAVE(ID): ");
		scanf("%ld",&aux.clave);
		fflush(stdin);
		printf("DESCRIPCION: ");
		scanf("%s",aux.d);
		fflush(stdin);
		printf("INGRESE EL TIPO DE DATO: ");
		scanf("%d",&aux.tipo);
		fflush(stdin);
		aux.b='A';
		fwrite(&aux,sizeof(aux),1,datos);
		printf("AGREGAR OTRA PERSONA?: ");
		scanf("%c",&op);
		fflush(stdin);	
		}while((op=='S')||(op=='s'));
		}
	fclose(datos);
	if((datos=fopen("datos.dat","rb+"))==NULL){
		printf("\nNO SE PUDO LEER EL ARCHIVO");
	}
	fread(&aux,sizeof(aux),1,datos);
	while(!feof(datos)){
		pila *actual = armarpila(aux,inicio);
		printf("%ld  /  %s  /  %d  /  %c  \n",aux.clave,aux.d,aux.tipo,aux.b);
		fread(&aux,sizeof(aux),1,datos);
	}
	pila *actual = (pila*)malloc(sizeof(pila));
	actual = inicio;
	if(actual!=NULL){
		printf("PILA");
		while(actual!=NULL){
			printf("%ld  /  %d  /  %c  \n",aux.clave,aux.tipo,aux.b);
			actual = actual->siguiente;
		}
	}
	else{
		printf("\nPILA VACIA");
	}
	system("pause");	
	fclose(datos);
	return 0;
}

pila* armarpila(struct d aux,struct pila *inicio){
	pila *nuevo = (struct pila*)malloc(sizeof(struct pila));
	if(nuevo->d.tipo|(1<<4)==1){
			nuevo->d.clave = aux.clave;
        	nuevo->d.b = aux.b;
	        nuevo->siguiente = NULL;
	        inicio = nuevo;
	}
	else{
			printf("\nREGISTRO NO ENCONTRADO");
	}
    return inicio;
}
