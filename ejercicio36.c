/*EJERCICIO 36: Hacer un programa que lea al archivo "contactos.dat" creado en el Ejercicio 35
y crear una lista, en memoria dinámica, ordenada alfabéticamente.
Una vez creada la lista guardarla en un archivo de organización directa 
llamado "contactos_ordenados.dat" imprimiendola en pantalla.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct datos{
	char nombre[20];
	char apellido[20];
	int edad;
	char mail[100];
	char telefono[20];
	char id[10];
}datos;

typedef struct nodo{
    datos datos_t;
    struct nodo *siguiente;
}nodo;

void insertarnodo(nodo *primero,nodo *ultimo,nodo *nuevo,datos aux);
void mostrarlista(nodo *primero,nodo *actual);
int main(){
	FILE *contacto,*contacto_t;
	int pos;
	datos aux;
	nodo *primero,*ultimo,*nuevo,*actual;
	primero=ultimo=nuevo=actual=NULL;
	if((contacto=fopen("contactos.dat","rb+"))==NULL){
		printf("No se pudo abrir el archivo!!");
	}
	if((contacto_t=fopen("contactos_ordenados.dat","wb"))==NULL){
		printf("No se pudo abrir el archivo!!");
	}
	printf("REGISTROS EN EL ARCHIVO CONTACTOS.DAT\n");
	fread(&aux,sizeof(aux),1,contacto);
	while(!feof(contacto)){
		printf("%s |   %s   |  %s  |   %d   |   %s   |  %s\n",aux.id,aux.nombre,aux.apellido,aux.edad,aux.telefono,aux.mail);
		fwrite(&aux,sizeof(aux),1,contacto_t);
		fflush(stdin);
		printf("INGRESE EL NUEVO ID: ");
	    scanf("%s",&aux.id);
	    fflush(stdin);
	    insertarnodo(primero,ultimo,nuevo,aux);
	    pos=ftell(contacto_t)-sizeof(aux);
        fseek(contacto_t,pos,SEEK_SET);
	    fwrite(&aux,sizeof(aux),1,contacto_t);
		fread(&aux,sizeof(aux),1,contacto);
	}
	fclose(contacto_t);
	system("pause");
	printf("\n");
	if((contacto_t=fopen("contactos_ordenados.dat","rb+"))==NULL){
		printf("No se pudo abrir el archivo!!");
	}
	printf("REGISTROS EN EL ARCHIVO CONTACTOS_ORDENADOS.DAT\n");
	printf("ID    |   NOMBRE   | APELLIDO |  EDAD  |    TELEFONO    |    MAIL\n");
	printf("--------------------------------------------------------------------\n");
	fread(&aux,sizeof(aux),1,contacto_t);
	while(!feof(contacto_t)){
		printf("%s     |   %s   |  %s  |   %d   |   %s   |  %s\n",aux.id,aux.nombre,aux.apellido,aux.edad,aux.telefono,aux.mail);	
		fread(&aux,sizeof(aux),1,contacto_t);
	}
    mostrarlista(primero,actual);
	fclose(contacto);
	fclose(contacto_t);
	return 0;
}

void insertarnodo(nodo *primero,nodo *ultimo,nodo *nuevo,datos aux){
	nuevo = (nodo*)malloc(sizeof(nodo));
	strcpy(nuevo->datos_t.nombre,aux.nombre);
	strcpy(nuevo->datos_t.apellido,aux.apellido);
	nuevo->datos_t.edad = aux.edad;
	strcpy(nuevo->datos_t.telefono,aux.telefono);
	strcpy(nuevo->datos_t.mail,aux.mail);
	
	if(primero == NULL){
		primero = nuevo;
		nuevo->siguiente = NULL;
		ultimo = nuevo;
		printf("NODO CREADO CORRECTAMENTE\n");
	}
	else{
		ultimo->siguiente = nuevo;
		nuevo->siguiente = NULL;
		ultimo = nuevo;
		printf("NODO CREADO CORRECTAMENTE(2)\n");
	}
}

void mostrarlista(nodo *primero,nodo *actual){
	actual = (nodo*)malloc(sizeof(nodo));
	actual = primero;
	if(primero != NULL){
		while(primero != NULL){
			printf("LISTA DE CONTACTOS\n");
			printf("%s |   %s   |  %s  |   %d   |   %s   |  %s\n",actual->datos_t.id,actual->datos_t.nombre,actual->datos_t.apellido,actual->datos_t.edad,actual->datos_t.telefono,actual->datos_t.mail);
			free(actual);
            actual = actual->siguiente;
		}
	}
	else{
		printf("LA LISTA ESTA VACIA\n");
	}
}