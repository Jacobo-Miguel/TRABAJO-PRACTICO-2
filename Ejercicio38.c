/*EJERCICIO 38:
Hacer una cola con los valores muestreados de un cuarto de ciclo de una señal sinusoidal, en 8 bits,
para luego recorrerla y recomponer la señal completa. 
Las muetras deberán ir de 127 a -127 utilizando el bit más significativo en 1 para los valores negativos
y en 0 para los valores positivos. Imprimir en pantalla los valores.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct cola{
	unsigned char dato;
	struct cola *siguiente;
	struct cola *anterior;
}cola_t;

void mostrarcola(cola_t *primero, cola_t *ultimo);
int main(){
	int i;
	cola_t *primero, *ultimo;
	primero=ultimo=NULL;
	
	 for(i=0;i<128;i++){
		cola_t *nuevo = (cola_t*)malloc(sizeof(cola_t));
		nuevo->dato = i;
		if(primero==NULL){
			primero = nuevo;
			primero->siguiente = NULL;
			nuevo->anterior = ultimo;
			ultimo = nuevo;
		}
		else{
			ultimo->siguiente = nuevo;
			nuevo->siguiente = NULL;
			nuevo->anterior = ultimo;
			ultimo = nuevo;
		}
	}
	
	mostrarcola(primero,ultimo);
	printf("\n");
	return 0;
}

void mostrarcola(cola_t *primero, cola_t *ultimo){
	cola_t *actual = (cola_t*)malloc(sizeof(cola_t));
	actual = primero;
	if(actual!=NULL){
		while(actual!=NULL){
			printf("%d |",actual->dato);
			actual = actual->siguiente;
	    }
	}
	else{
		printf("\nLa cola esta vacia");
	}
	
	cola_t *temporal = (cola_t*)malloc(sizeof(cola_t));
	temporal = ultimo;
	if(temporal!=NULL){
		while(temporal!=NULL){
			temporal = temporal->anterior;
			printf("%d |",temporal->dato);
		}
	} 
	else{
		printf("\nLa cola esta vacia");
	}
}