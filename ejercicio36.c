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

void mostrarlista(nodo *primero, FILE *contacto_t);
int main(){
	FILE *contacto,*contacto_t;
	datos aux;
	nodo *primero,*ultimo,*r;
	primero=ultimo=NULL;
	if((contacto_t=fopen("contactos_ordenados.dat","wb"))==NULL){
		printf("No se pudo abrir el archivo!!");
	}
	if((contacto=fopen("contactos.dat","rb+"))==NULL){
		printf("No se pudo abrir el archivo!!");
	}
	else{
	    printf("REGISTROS EN EL ARCHIVO CONTACTOS.DAT\n");
	    fread(&aux,sizeof(aux),1,contacto);
	    while(!feof(contacto)){
	    	printf("%s |   %s   |  %s  |   %d   |   %s   |  %s\n",aux.id,aux.nombre,aux.apellido,aux.edad,aux.telefono,aux.mail);
	    	nodo *nuevo = (nodo*)malloc(sizeof(nodo));
	    	fflush(stdin);
	    	printf("Ingrse el id nuevo: ");
	    	scanf("%s",&aux.id);
	     	strcpy(nuevo->datos_t.id,aux.id);
	        strcpy(nuevo->datos_t.nombre,aux.nombre);
	        strcpy(nuevo->datos_t.apellido,aux.apellido);
	        nuevo->datos_t.edad = aux.edad;
	        strcpy(nuevo->datos_t.telefono,aux.telefono);
	        strcpy(nuevo->datos_t.mail,aux.mail);
	
	        if(primero == NULL){
		        primero = nuevo;
		        nuevo->siguiente = NULL;
		        ultimo = nuevo;
	        }
	        else{
	            r = primero;
	    	    while(1){
	    	    	if(r->datos_t.nombre < nuevo->datos_t.nombre){
	    			    nuevo->siguiente = primero;
	    		    	primero = nuevo;
	    		    	break;
				    }
				while(r->siguiente!=NULL){
					if(r->siguiente->datos_t.nombre < nuevo->datos_t.nombre){
						r = r->siguiente;
					}
					else{
						break;
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
	    fread(&aux,sizeof(aux),1,contacto);
	}	
	fclose(contacto);
	mostrarlista(primero,contacto_t);
	fclose(contacto_t);
	}
	
	system("pause");
	printf("\n");
	if((contacto_t=fopen("contactos_ordenados.dat","rb"))==NULL){
		printf("No se pudo abrir el archivo!!");
	}
	else{
	    printf("REGISTROS EN EL ARCHIVO CONTACTOS_ORDENADOS.DAT\n");
	    printf("ID    |   NOMBRE   | APELLIDO |  EDAD  |    TELEFONO    |    MAIL\n");
	    printf("--------------------------------------------------------------------\n");
	    fread(&aux,sizeof(aux),1,contacto_t);
    	    while(!feof(contacto_t)){
		    printf("%s     |   %s   |  %s  |   %d   |   %s   |  %s\n",aux.id,aux.nombre,aux.apellido,aux.edad,aux.telefono,aux.mail);	
		    fread(&aux,sizeof(aux),1,contacto_t);
    	    }
	}
	fclose(contacto_t);
	return 0;
}

void mostrarlista(nodo *primero, FILE *contacto_t){
	nodo *actual = (nodo*)malloc(sizeof(nodo));
	actual = primero;
	if(primero != NULL){
		printf("LISTA DE CONTACTOS\n");
		while(primero != NULL){
			printf("%s |   %s   |  %s  |   %d   |   %s   |  %s\n",actual->datos_t.id,actual->datos_t.nombre,actual->datos_t.apellido,actual->datos_t.edad,actual->datos_t.telefono,actual->datos_t.mail);
			fwrite(&actual->datos_t,sizeof(actual->datos_t),1,contacto_t);
	    	        actual = actual->siguiente;
		}
	}
	else{
		printf("LA LISTA ESTA VACIA\n");
	}
}
