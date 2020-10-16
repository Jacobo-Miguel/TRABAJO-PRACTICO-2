/*EJERCICIO 35:Hacer un programa que tome los datos de contacto de una persona (Nombre, Apellido, edad, teléfono, mail) y
los cargue, en forma directa, en una pila de memoria dinámica. 
Imprimir en pantalla y cargar en un archivo llamado "contactos.dat", de organización secuencial,
los registros ingresados por el usuario si la persona tiene una edad mayor a 21 años.*/
#include <stdio.h>
#include <stdlib.h>

struct datos{
	char nombre[20];
	char apellido[20];
	int edad;
	char mail[100];
	char telefono[20];
	char id[10];
};

struct nodo {
	struct datos d;
	struct nodo *siguiente;
};

int main(){
	FILE *contacto;
	struct datos aux;
	struct nodo *inicio, *actual, *nuevo;
	char op;
	inicio=actual=nuevo=NULL;


    if((contacto=fopen("contactos.dat","wb"))==NULL){
    	printf("No se pudo abrir el archivo");
	}
	else{
		do{
		nuevo = (struct nodo*)malloc(sizeof(struct nodo));
         	fflush(stdin);
        	printf("INGRESE EL NOMBRE: ");
        	scanf("%s",&nuevo->d.nombre);
	        fflush(stdin);
	        printf("INGRESE EL APELLIDO: ");
	        scanf("%s",&nuevo->d.apellido);
                fflush(stdin);
   	        printf("INGRESE LA EDAD: ");
	        scanf("%d",&nuevo->d.edad);
	        fflush(stdin);
	        printf("INGRESE EL MAIL: ");
	        scanf("%s",&nuevo->d.mail);
	        fflush(stdin);
	        printf("INGRESE EL TELEFONO: ");
	        scanf("%s",&nuevo->d.telefono);
	        fflush(stdin);
	        printf("INGRESE EL ID DEL REGISTRO: ");
	        scanf("%s",&nuevo->d.id);
	        fflush(stdin);
	        nuevo->siguiente = inicio;
	        inicio = nuevo;
	        fflush(stdin);
	        printf("AGREGAR OTRA PERSONA?: ");
	        scanf("%c",&op);
			
		}while((op=='S') || (op=='s'));
		actual = (struct nodo*)malloc(sizeof(struct nodo));
                actual = inicio;
                if(actual != NULL){
                    while(actual != NULL){
   	    	          if(actual->d.edad>21){
   	    	          	fwrite(&actual->d,sizeof(actual->d),1,contacto);
		           }
   	    	          actual = actual->siguiente;	
	            }
                }
                else{
          	   printf("NO HAY ELEMENTOS EN LA PILA\n");
                }
		system("pause");
		fclose(contacto);
	}
	
	if((contacto=fopen("contactos.dat","rb"))==NULL){
		printf("No se pudo leer el archivo");
	}
	else{
		system("cls");
		fread(&aux,sizeof(aux),1,contacto);
		printf("REGISTROS DE PERSONAS CON EDAD MAYOR A 21 ANOS\n");
		printf("ID    |   NOMBRE   | APELLIDO |  EDAD  |    TELEFONO    |    MAIL\n");
		printf("--------------------------------------------------------------------\n");
		while(!feof(contacto)){
				
			printf("%s |   %s   |  %s  |   %d   |   %s   |  %s\n",aux.id,aux.nombre,aux.apellido,aux.edad,aux.telefono,aux.mail);
			fread(&aux,sizeof(aux),1,contacto);
		}
		fclose(contacto);
	}
	return 0;
}
