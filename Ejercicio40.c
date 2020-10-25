/*EJERCICIO 40:

Utilizando el archivo “potencia.dat” creado en el Ejercicio 39, realizar una función que pase como parámetro, entre otros datos, la clave del registro (id).

La función ubicará el registro correspondiente al id pasado como parámetro,
y utilizando punteros imprimirá la primera palabra del campo "desc" en forma inversa, 
además cambiará el estado del bit 3 para luego actualizar el archivo. 
Además, se agregará a una pila la potencia cuando los bits 0 y 2, del campo estado, estén encendidos, 
en caso contrario se agregará el registro al archivo “salida.dat” de organización secuencial.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct datos{
	char desc[60];
	unsigned char potencia;
	unsigned int estado;
	int id;
}datos_t;

typedef struct pila{
	datos_t datos;
	struct pila *siguiente;
}pila_t;

void funcion(datos_t datos, pila_t * inicio,FILE *potencia);

int main(){
	FILE *potencia;
	datos_t datos;
	pila_t *inicio=NULL;
	if((potencia=fopen("potencia.dat","rb"))==NULL){
		printf("No se pudo abrir el archivo");
	}
	else{
		funcion(datos,inicio,potencia);  	
	}
	fclose(potencia);
	return 0;
}

void funcion(datos_t datos, pila_t * inicio,FILE *potencia){
	FILE *salida;
	int i;
	fread(&datos,sizeof(datos),1,potencia);
		printf("DATOS DEL ARCHIVO POTENCIA.DAT\n");
		printf("ID  |  DESCRIPCION  |  POTENCIA  |  ESTADO");
		while(!feof(potencia)){
			printf("\n%d   |  %s         |     %d      |     %d",datos.id,datos.desc,datos.potencia,datos.estado);
			while(datos.desc!=" "){ 
				printf("%s",datos.desc[i]);
			}
			fread(&datos,sizeof(datos),1,potencia);
		}
	pila_t *nuevo = (pila_t*)malloc(sizeof(pila_t));
	if(nuevo->datos.estado|(1<<0)==1 && nuevo->datos.estado|(1<<2)==1){
		nuevo->datos.potencia = datos.potencia;
		nuevo->siguiente = NULL;
		inicio = nuevo;
		printf("\nPILA CREADA");
	}
	else{
		if((salida=fopen("salida.dat","wb"))==NULL){
			printf("No se pudo crear el archivo");
		}
		else{
			fwrite(&datos,sizeof(datos),1,salida);
			fclose(salida);
			printf("\nARCHIVO CREADO");
		}
	}
}