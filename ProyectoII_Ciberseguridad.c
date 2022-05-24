#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListaAtaques ListaAtaques;
typedef struct ListaDelincuentes ListaDelincuentes;
typedef struct Nodo Nodo;
typedef char string[300];

typedef struct
{
    string codigoA;
    string nombre;
    string descripcion;
    string canales;
    string tipoArchivo;
    int tamano;
}informacionCiberataque;

typedef struct
{
    string codigoD;
    string nombreGrupo;
    string paisOrigen;
    string listaCiberataques;
    string tipoArchivo;
    int tamano;
}informacionCiberdelincuente;

struct Nodo
{
    informacionCiberataque dato;
    informacionCiberdelincuente dato2;
    Nodo *siguiente;
};

struct ListaAtaques
{
    Nodo *inicio;
};

ListaAtaques *lista1(void)
{
	ListaAtaques *A;
	A = (ListaAtaques *) malloc(sizeof(ListaAtaques));
	A->inicio = NULL;
	return A;
}

struct ListaDelincuentes
{
    Nodo *inicio2;
};

ListaDelincuentes *lista2(void)
{
    ListaDelincuentes *D;
	D = (ListaDelincuentes *) malloc(sizeof(ListaDelincuentes));
	D->inicio2 = NULL;
	return D;
}

//-----------------------  1. Registro de tipo de ciberataque --------------------------------//

void lecturaDatosAtaques(informacionCiberataque *infoA)
{
    int contador = 0;

    printf("\nIndique el codigo: ");
    gets(infoA->codigoA);

    printf("\nIngrese el nombre: ");
    gets(infoA->nombre);

    printf("\nIngrese la descripcion: ");
    gets(infoA->descripcion);

    printf("\nIngrese los canales por donde se puede dar el ataque: ");
    gets(infoA->canales);
}

void insercionArchivosAtaques(informacionCiberataque *infoA)
{
    int indice = 0;

    FILE *archivo;
    string ruta;
    strcpy(ruta, ".\\InfoAtaques\\");
    strcat(ruta, infoA->codigoA);
    strcpy(infoA->tipoArchivo, ruta);
    strcat(infoA->tipoArchivo, ".txt");

    archivo = fopen(infoA->tipoArchivo, "a+");
    fprintf(archivo, "%s; %s; %s; %s;", infoA->codigoA, infoA->nombre, infoA->descripcion, infoA->canales);
}

void creacionTxtCodigo(informacionCiberataque *infoA)
{
    FILE *archivo;
    string ruta;
    strcpy(ruta,".\\InfoAtaques\\Codigos");
    strcpy(infoA->tipoArchivo, ruta);
    strcat(infoA->tipoArchivo, ".txt");

    archivo = fopen(infoA->tipoArchivo, "a+");
    fprintf(archivo, "%s;", infoA->codigoA);
}

void insertarAtaque(ListaAtaques *A, informacionCiberataque infoA)
{
	int contador = 0;
	int cantidadPreguntas;

    
	printf("Cuantos tipos de ciberataque desea registrar ");
	scanf("%d", &cantidadPreguntas);
	getchar();
	printf("\n\n");
	
	//infoV.cantvehiculos = 1;
    lecturaDatosAtaques(&infoA);
    Nodo *n, *aux;

    if(A->inicio == NULL) //Valida si la lista esta vacia
    {
        A->inicio = (Nodo *) malloc(sizeof(Nodo));
        A->inicio->dato = infoA;
        A->inicio->siguiente = NULL;	
    }
    else
    {
        n = A->inicio;
        while(n != NULL)
        {
            aux = n;
            n = n->siguiente;
        }
        aux->siguiente = (Nodo *) malloc(sizeof(Nodo));
        aux->siguiente->siguiente = NULL;
        aux->siguiente->dato = infoA;
    }
    //infoV.cantvehiculos++;
    
    insercionArchivosAtaques(&infoA);
    creacionTxtCodigo(&infoA);
	printf("\n");
	printf("El registro de los ataques se ha realizado exitosamente\n");
}

//-----------------------  Eliminar información --------------------------------//

void eliminarAtaqueTotal(informacionCiberataque *infoA, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;

	while(indice < infoA->tamano)
	{
		if(strcmp(lista[indice], infoA->codigoA) == 0)
		strcpy(lista[indice], "");
		indice++;
	}

	string rutaAux;
	strcpy(rutaAux, ".\\InfoAtaques\\Codigos");
	strcpy(infoA->tipoArchivo, rutaAux);
	strcat(infoA->tipoArchivo, ".txt");
	archivoAux = fopen(infoA->tipoArchivo, "a+");
	
	indice = 0;
	while(indice < infoA->tamano)
	{	
		if(indice == (infoA->tamano)-1)
		{
			fprintf(archivoAux,"%s", lista[indice]);
		}
		else
		{
			fprintf(archivoAux,"%s;", lista[indice]);
		}
		indice++;
	}
}

void datosAtaquesTotales(informacionCiberataque *infoA)
{
	FILE *archivo = NULL; 
	
	string listaAtaques[100];
	infoA->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\InfoAtaques\\Codigos");
	strcpy(infoA->tipoArchivo, ruta);
	strcat(infoA->tipoArchivo, ".txt");
	
	archivo = fopen(infoA->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaAtaques[indice], token);
      			infoA->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	remove(infoA->tipoArchivo);

	eliminarAtaqueTotal(infoA, listaAtaques);
}

void eliminarCiberataque(informacionCiberataque *infoA)
{
	FILE *archivo;
	string ruta;
	strcpy(ruta, ".\\InfoAtaques\\");
	
	printf("Ingrese el codigo del tipo de ataque que desea eliminar: ");
	gets(infoA->codigoA);
	
	strcat(ruta, infoA->codigoA);
	strcpy(infoA->tipoArchivo, ruta);
	strcat(infoA->tipoArchivo, ".txt");
	
	archivo = fopen(infoA->tipoArchivo, "w");

	fclose(archivo);
	
	remove(infoA->tipoArchivo);

	datosAtaquesTotales(infoA);
	printf("\nEl tipo de ciberataque ha sido eliminado\n");
	exit(-1);
}

//-----------------------  Modificar información --------------------------------//

void extraerListaAtaques(informacionCiberataque *infoA, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;
	int respuesta;
	string nombre;
	string descripcion;
	string canal;
	string espacio = " ";
	
	printf("Que desea modificar?\n1.Nombre\n2.Descripcion\n3.Canal por donde se puede dar el ataque\n");
	scanf("%d", &respuesta);
	getchar();
	
	if(respuesta == 1)
	{
		printf("Ingrese el nuevo nombre: ");
		gets(nombre);
		strcpy(lista[1], espacio);
		strcat(lista[1], nombre);
	}
	
	else if(respuesta == 2)
	{
		printf("Ingrese la nueva descripcion: ");
		gets(descripcion);
		strcpy(lista[2], espacio);
		strcat(lista[2], descripcion);
	}
	else
	{
		printf("Ingrese el nuevo canal: ");
		gets(canal);
		strcpy(lista[3], espacio);
		strcat(lista[3], canal);
    } 
	
	string rutaAux;
	strcpy(rutaAux, ".\\InfoAtaques\\");
	strcat(rutaAux,infoA->codigoA);
	strcpy(infoA->tipoArchivo, rutaAux);
	strcat(infoA->tipoArchivo, ".txt");
	archivoAux = fopen(infoA->tipoArchivo, "a+");
	
	while(indice < infoA->tamano)
	{	
		fprintf(archivoAux,"%s;", lista[indice]);
		indice++;
	}
	printf("\n");
	printf("La modificacion se realizo exitosamente");
	printf("\n");
	printf("\n");
	exit(-1);
}

void modificarInfoV(informacionCiberataque *infoA)
{
	FILE *archivo = NULL; 
	
	string listaAtaques[100];
	infoA->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	printf("Ingrese el codigo del tipo de ciberataque que desea modificar: ");
	gets(infoA->codigoA);
	
	string ruta;
	strcpy(ruta, ".\\InfoAtaques\\");
	strcat(ruta, infoA->codigoA);
	strcpy(infoA->tipoArchivo, ruta);
	strcat(infoA->tipoArchivo, ".txt");
	
	archivo = fopen(infoA->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaAtaques[indice], token);
      			infoA->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	remove(infoA->tipoArchivo);

	extraerListaAtaques(infoA, listaAtaques);
}

//-----------------------  Consultar informacion --------------------------------//

void mostrarAtaquesTotales(informacionCiberataque *infoA, string lista[])
{
	FILE *archivo = NULL; 
	
	int indice2 = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	string ruta;
	

	while(indice2 < infoA->tamano)
	{
		int indice = 0;
		strcpy(ruta, ".\\InfoAtaques\\");
		strcat(ruta,lista[indice2]);
		strcpy(infoA->tipoArchivo, ruta);
		strcat(infoA->tipoArchivo, ".txt");

		archivo = fopen(infoA->tipoArchivo, "a+");

		printf("\n\n ");
		if(archivo)
		{
			while(fgets(linea, 300, archivo))
			{
				token = strtok(linea, delimitador);
				while( token != NULL ) 
				{
					if(indice == 1)
					{
						printf("Nombre:           %s\n", token);
					}
					else if(indice == 2)
					{
						printf(" Descripcion:      %s\n", token);
					}
					else if(indice == 3)
					{
						printf(" Canales:          %s\n", token);
					}	

					indice++;
					token = strtok(NULL, delimitador);
				}
			}
		}
		indice2++;
	}	
	fclose(archivo);
	printf("\n");
	printf("\n");
}

void extraerDatosAtaques(informacionCiberataque *infoA)
{
	FILE *archivo = NULL; 

	string listaAtaques[100];
	infoA->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\InfoAtaques\\Codigos");
	strcpy(infoA->tipoArchivo, ruta);
	strcat(infoA->tipoArchivo, ".txt");
	
	archivo = fopen(infoA->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaAtaques[indice], token);
      			infoA->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	mostrarAtaquesTotales(infoA, listaAtaques);
}

//------------------------ 2. Registro de ciberdelincuente --------------------------------//


void lecturaDatosDelincuente(informacionCiberdelincuente *infoD)
{	
	printf("Ingrese el codigo de identificacion: ");
	gets(infoD->codigoD);
	
	printf("\nIngrese el nombre del grupo: ");
	gets(infoD->nombreGrupo);
	
	printf("\nIngrese el pais de origen: ");
	gets(infoD->paisOrigen);
	
	printf("\nIngrese la lista de ciberataques mas reconocidos que ha cometido: ");
	gets(infoD->listaCiberataques);
}

void creacionArchivosDelincuente(informacionCiberdelincuente *infoD)
{
	FILE *archivo; 
	string ruta;
	strcpy(ruta, ".\\InfoDelincuentes\\");
	
	strcat(ruta, infoD->codigoD);
	strcpy(infoD->tipoArchivo, ruta);
	strcat(infoD->tipoArchivo, ".txt");
	
	archivo = fopen(infoD->tipoArchivo, "a+");
	fprintf(archivo,"%s; %s; %s; %s;", infoD->codigoD, infoD->nombreGrupo, infoD->paisOrigen, infoD->listaCiberataques);
	fclose(archivo);
}


void insercionCodigos(informacionCiberdelincuente *infoD)
{
	FILE *archivo; 
	string ruta;
	strcpy(ruta, ".\\InfoDelincuentes\\Codigos");
	
	strcpy(infoD->tipoArchivo, ruta);
	strcat(infoD->tipoArchivo, ".txt");
	
	archivo = fopen(infoD->tipoArchivo, "a+");
	fprintf(archivo,"%s; ", infoD->codigoD);
}

void insertarDatosCliente(ListaDelincuentes *D, informacionCiberdelincuente infoD)
{
	lecturaDatosDelincuente(&infoD);
	Nodo *n, *aux;

	if(D->inicio2 == NULL) //Valida si la lista esta vacia
	{
			D->inicio2 = (Nodo *) malloc(sizeof(Nodo));
			D->inicio2->dato2 = infoD;
			D->inicio2->siguiente = NULL;
	}
	else
	{
		n = D->inicio2;
		while(n != NULL)
		{
			aux = n;
			n = n->siguiente;
		}
		aux->siguiente = (Nodo *) malloc(sizeof(Nodo));
		aux->siguiente->siguiente = NULL;
		aux->siguiente->dato2 = infoD;
	}		
	creacionArchivosDelincuente(&infoD);
	insercionCodigos(&infoD);
	printf("\n");
	printf("\n");
	printf("La informacion se ha registrado exitosamente");
	exit(-1);
	printf("\n");
	printf("\n");
}

//-----------------------  Eliminar información --------------------------------//

void eliminarDelincuenteTotal(informacionCiberdelincuente *infoD, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;

	while(indice < infoD->tamano)
	{
		if(strcmp(lista[indice], infoD->codigoD) == 0)
		strcpy(lista[indice], "");
		indice++;
	}

	string rutaAux;
	strcpy(rutaAux, ".\\InfoDelincuentes\\Codigos");
	strcpy(infoD->tipoArchivo, rutaAux);
	strcat(infoD->tipoArchivo, ".txt");
	archivoAux = fopen(infoD->tipoArchivo, "a+");
	
	indice = 0;
	while(indice < infoD->tamano)
	{	
		if(indice == (infoD->tamano)-1)
		{
			fprintf(archivoAux,"%s", lista[indice]);
		}
		else
		{
			fprintf(archivoAux,"%s;", lista[indice]);
		}
		indice++;
	}
}

void datosDelincuentesTotales(informacionCiberdelincuente *infoD)
{
	FILE *archivo = NULL; 
	
	string listaDelincuentes[100];
	infoD->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\InfoDelincuentes\\Codigos");
	strcpy(infoD->tipoArchivo, ruta);
	strcat(infoD->tipoArchivo, ".txt");
	
	archivo = fopen(infoD->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaDelincuentes[indice], token);
      			infoD->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	remove(infoD->tipoArchivo);

	eliminarDelincuenteTotal(infoD, listaDelincuentes);
}

void eliminarCiberDelincuente(informacionCiberdelincuente *infoD)
{
	FILE *archivo;
	string ruta;
	strcpy(ruta, ".\\InfoDelincuentes\\");
	
	printf("Ingrese el codigo del ciberdelincuente al cual desea eliminar la informacion: ");
	gets(infoD->codigoD);
	
	strcat(ruta, infoD->codigoD);
	strcpy(infoD->tipoArchivo, ruta);
	strcat(infoD->tipoArchivo, ".txt");
	
	archivo = fopen(infoD->tipoArchivo, "w");

	fclose(archivo);
	
	remove(infoD->tipoArchivo);

	datosDelincuentesTotales(infoD);
	printf("\nLa informacion del ciberdelincuente ha sido eliminada\n");
	exit(-1);
}

//-----------------------  Modificar información --------------------------------//

void extraerListaDelincuentes(informacionCiberdelincuente *infoD, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;
	int respuesta;
	string nombre;
	string pais;
	string ciberataques;
	string espacio = " ";
	
	printf("Que desea modificar?\n1.Nombre del grupo\n2.Pais de origen\n3.Lista de ciberataques mas reconocidos\n");
	scanf("%d", &respuesta);
	getchar();
	
	if(respuesta == 1)
	{
		printf("Ingrese el nuevo nombre del grupo: ");
		gets(nombre);
		strcpy(lista[1], espacio);
		strcat(lista[1], nombre);
	}
	
	else if(respuesta == 2)
	{
		printf("Ingrese el nuevo pais de origen: ");
		gets(pais);
		strcpy(lista[2], espacio);
		strcat(lista[2], pais);
	}
	else
	{
		printf("Ingrese la nueva lista de ciberataques: ");
		gets(ciberataques);
		strcpy(lista[3], espacio);
		strcat(lista[3], ciberataques);
    } 
	
	string rutaAux;
	strcpy(rutaAux, ".\\InfoDelincuentes\\");
	strcat(rutaAux,infoD->codigoD);
	strcpy(infoD->tipoArchivo, rutaAux);
	strcat(infoD->tipoArchivo, ".txt");
	archivoAux = fopen(infoD->tipoArchivo, "a+");
	
	while(indice < infoD->tamano)
	{	
		fprintf(archivoAux,"%s;", lista[indice]);
		indice++;
	}
	printf("\n");
	printf("La modificacion se realizo exitosamente");
	printf("\n");
	printf("\n");
	exit(-1);
}

void modificarInfoD(informacionCiberdelincuente *infoD)
{
	FILE *archivo = NULL; 
	
	string listaDelincuentes[100];
	infoD->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	printf("Ingrese el codigo del ciberdelincuente que desea modificar: ");
	gets(infoD->codigoD);
	
	string ruta;
	strcpy(ruta, ".\\InfoDelincuentes\\");
	strcat(ruta, infoD->codigoD);
	strcpy(infoD->tipoArchivo, ruta);
	strcat(infoD->tipoArchivo, ".txt");
	
	archivo = fopen(infoD->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaDelincuentes[indice], token);
      			infoD->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	remove(infoD->tipoArchivo);

	extraerListaDelincuentes(infoD, listaDelincuentes);
}

//-----------------------  Consultar informacion --------------------------------//

void mostrarDelincuentesTotales(informacionCiberdelincuente *infoD, string lista[])
{
	FILE *archivo = NULL; 
	
	int indice2 = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	string ruta;
	

	while(indice2 < infoD->tamano)
	{
		int indice = 0;
		strcpy(ruta, ".\\InfoDelincuentes\\");
		strcat(ruta,lista[indice2]);
		strcpy(infoD->tipoArchivo, ruta);
		strcat(infoD->tipoArchivo, ".txt");

		archivo = fopen(infoD->tipoArchivo, "a+");

		printf("\n\n ");
		if(archivo)
		{
			while(fgets(linea, 300, archivo))
			{
				token = strtok(linea, delimitador);
				while( token != NULL ) 
				{
					if(indice == 1)
					{
						printf("Nombre del grupo:                  %s\n", token);
					}
					else if(indice == 2)
					{
						printf(" Pais de origen:                    %s\n", token);
					}
					else if(indice == 3)
					{
						printf(" Ciberataques mas reconocidos:      %s\n", token);
					}	

					indice++;
					token = strtok(NULL, delimitador);
				}
			}
		}
		indice2++;
	}	
	fclose(archivo);
	printf("\n");
	printf("\n");
}

void extraerDatosDelincuentes(informacionCiberdelincuente *infoD)
{
	FILE *archivo = NULL; 

	string listaDelincuentes[100];
	infoD->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\InfoDelincuentes\\Codigos");
	strcpy(infoD->tipoArchivo, ruta);
	strcat(infoD->tipoArchivo, ".txt");
	
	archivo = fopen(infoD->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaDelincuentes[indice], token);
      			infoD->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	mostrarDelincuentesTotales(infoD, listaDelincuentes);
}

int main()
{
    ListaAtaques *A;
    A = lista1();
    informacionCiberataque ataques;

    ListaDelincuentes *D;
    D = lista2();
    informacionCiberdelincuente delincuentes;

    //insertarAtaque(A, ataques);
    //eliminarCiberataque(&ataques);
    //modificarInfoV(&ataques);
	//extraerDatosAtaques(&ataques);

    //insertarDatosCliente(D, delincuentes);
    //eliminarCiberDelincuente(&delincuentes);
    //modificarInfoD(&delincuentes);
	//extraerDatosDelincuentes(&delincuentes);

    return 0;
}
