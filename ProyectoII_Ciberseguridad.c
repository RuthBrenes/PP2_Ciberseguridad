#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct ListaAtaques ListaAtaques;
typedef struct ListaDelincuentes ListaDelincuentes;
typedef struct ListaPaises ListaPaises;
typedef struct Nodo Nodo;
typedef struct vertice vertice;
typedef struct arista arista;
typedef struct grafo grafo;
void menu();

typedef char string[300];

typedef struct
{
    string codigoA;
    string nombre;
    string descripcion;
    string canales;
    string tipoArchivo;
    int tamano;
}tipoCiberataque;

typedef struct
{
    string codigoD;
    string nombreGrupo;
    string paisOrigen;
    string listaCiberataques;
    string tipoArchivo;
    int tamano;
}informacionCiberdelincuente;

typedef struct
{
    string codigo;
	string nombre;
	string cantidadHabitantes;
	string continente;
} informacionPais;

typedef struct
{
	string paisOrigen;
	string paisDestino;
	string tipoCiberataque;
	string nombreCiberdelincuente;
	string tipoArchivo;
	string cantidadDatos;
	string tiempo;
	int tamano;
}informacionCiberataques; 

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

struct Nodo
{
    tipoCiberataque dato;
    informacionCiberdelincuente dato2;
	informacionPais dato3;
    Nodo *siguiente;
};

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

struct ListaPaises
{
    Nodo *inicio2;
};

ListaPaises *lista3(void)
{
    ListaPaises *D;
	D = (ListaPaises *) malloc(sizeof(ListaPaises));
	D->inicio2 = NULL;
	return D;
}


struct grafo
{
	vertice *inicioG;
};

struct vertice
{
	vertice *siguiente;
	arista *ady;
	string nombre;
};

struct arista
{
	arista *siguiente;
	vertice *ady;	
	informacionCiberataques dato3;
};

vertice *inicioG = NULL;

//-----------------------  1. Registro de tipo de ciberataque --------------------------------//

void lecturaDatosAtaques(tipoCiberataque *infoT)
{
    int contador = 0;

    printf("\nIndique el codigo: ");
    gets(infoT->codigoA);

    printf("\nIngrese el nombre: ");
    gets(infoT->nombre);

    printf("\nIngrese la descripcion: ");
    gets(infoT->descripcion);

    printf("\nIngrese los canales por donde se puede dar el ataque: ");
    gets(infoT->canales);
}

void insercionArchivosAtaques(tipoCiberataque *infoT)
{
    int indice = 0;

    FILE *archivo;
    string ruta;
    strcpy(ruta, ".\\tipoAtaques\\");
    strcat(ruta, infoT->codigoA);
    strcpy(infoT->tipoArchivo, ruta);
    strcat(infoT->tipoArchivo, ".txt");

    archivo = fopen(infoT->tipoArchivo, "a+");
    fprintf(archivo, "%s; %s; %s; %s;", infoT->codigoA, infoT->nombre, infoT->descripcion, infoT->canales);
}

void creacionTxtCodigo(tipoCiberataque *infoT)
{
    FILE *archivo;
    string ruta;
    strcpy(ruta,".\\tipoAtaques\\Codigos");
    strcpy(infoT->tipoArchivo, ruta);
    strcat(infoT->tipoArchivo, ".txt");

    archivo = fopen(infoT->tipoArchivo, "a+");
    fprintf(archivo, "%s;", infoT->codigoA);
}

void insertarAtaque(ListaAtaques *A, tipoCiberataque infoT)
{
	int contador = 0;
	int cantidadPreguntas;

    
	printf("Cuantos tipos de ciberataque desea registrar: ");
	scanf("%d", &cantidadPreguntas);
	getchar();
	printf("\n");
	
    lecturaDatosAtaques(&infoT);
    Nodo *n, *aux;

    if(A->inicio == NULL) //Valida si la lista esta vacia
    {
        A->inicio = (Nodo *) malloc(sizeof(Nodo));
        A->inicio->dato = infoT;
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
        aux->siguiente->dato = infoT;
    }
    //infoV.cantvehiculos++;
    
    insercionArchivosAtaques(&infoT);
    creacionTxtCodigo(&infoT);
	printf("\n");
	printf("El registro de los ataques se ha realizado exitosamente\n");
}

//-----------------------  Eliminar información --------------------------------//

void eliminarAtaqueTotal(tipoCiberataque *infoT, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;

	while(indice < infoT->tamano)
	{
		if(strcmp(lista[indice], infoT->codigoA) == 0)
		strcpy(lista[indice], "");
		indice++;
	}

	string rutaAux;
	strcpy(rutaAux, ".\\tipoAtaques\\Codigos");
	strcpy(infoT->tipoArchivo, rutaAux);
	strcat(infoT->tipoArchivo, ".txt");
	archivoAux = fopen(infoT->tipoArchivo, "a+");
	
	indice = 0;
	while(indice < infoT->tamano)
	{	
		if(indice == (infoT->tamano)-1)
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

void datosAtaquesTotales(tipoCiberataque *infoT)
{
	FILE *archivo = NULL; 
	
	string listaAtaques[100];
	infoT->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\tipoAtaques\\Codigos");
	strcpy(infoT->tipoArchivo, ruta);
	strcat(infoT->tipoArchivo, ".txt");
	
	archivo = fopen(infoT->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaAtaques[indice], token);
      			infoT->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	remove(infoT->tipoArchivo);

	eliminarAtaqueTotal(infoT, listaAtaques);
}

void eliminarCiberataque(tipoCiberataque *infoT)
{
	FILE *archivo;
	string ruta;
	strcpy(ruta, ".\\tipoAtaques\\");
	
	printf("Ingrese el codigo del tipo de ataque que desea eliminar: ");
	gets(infoT->codigoA);
	
	strcat(ruta, infoT->codigoA);
	strcpy(infoT->tipoArchivo, ruta);
	strcat(infoT->tipoArchivo, ".txt");
	
	archivo = fopen(infoT->tipoArchivo, "w");

	fclose(archivo);
	
	remove(infoT->tipoArchivo);

	datosAtaquesTotales(infoT);
	printf("\nEl tipo de ciberataque ha sido eliminado\n");
	exit(-1);
}

//-----------------------  Modificar informacion --------------------------------//

void extraerListaAtaques(tipoCiberataque *infoT, string lista[])
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
	strcpy(rutaAux, ".\\tipoAtaques\\");
	strcat(rutaAux,infoT->codigoA);
	strcpy(infoT->tipoArchivo, rutaAux);
	strcat(infoT->tipoArchivo, ".txt");
	archivoAux = fopen(infoT->tipoArchivo, "a+");
	
	while(indice < infoT->tamano)
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

void modificarInfoV(tipoCiberataque *infoT)
{
	FILE *archivo = NULL; 
	
	string listaAtaques[100];
	infoT->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	printf("Ingrese el codigo del tipo de ciberataque que desea modificar: ");
	gets(infoT->codigoA);
	
	string ruta;
	strcpy(ruta, ".\\tipoAtaques\\");
	strcat(ruta, infoT->codigoA);
	strcpy(infoT->tipoArchivo, ruta);
	strcat(infoT->tipoArchivo, ".txt");
	
	archivo = fopen(infoT->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaAtaques[indice], token);
      			infoT->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	remove(infoT->tipoArchivo);

	extraerListaAtaques(infoT, listaAtaques);
}

//-----------------------  Consultar informacion --------------------------------//

void mostrarAtaquesTotales(tipoCiberataque *infoT, string lista[])
{
	FILE *archivo = NULL; 
	
	int indice2 = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	string ruta;
	

	while(indice2 < infoT->tamano)
	{
		int indice = 0;
		strcpy(ruta, ".\\tipoAtaques\\");
		strcat(ruta,lista[indice2]);
		strcpy(infoT->tipoArchivo, ruta);
		strcat(infoT->tipoArchivo, ".txt");

		archivo = fopen(infoT->tipoArchivo, "a+");

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

void extraerDatosAtaques(tipoCiberataque *infoT)
{
	FILE *archivo = NULL; 

	string listaAtaques[100];
	infoT->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\tipoAtaques\\Codigos");
	strcpy(infoT->tipoArchivo, ruta);
	strcat(infoT->tipoArchivo, ".txt");
	
	archivo = fopen(infoT->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaAtaques[indice], token);
      			infoT->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	mostrarAtaquesTotales(infoT, listaAtaques);
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

void insertarDatosDelincuente(ListaDelincuentes *D, informacionCiberdelincuente infoD)
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


//------------------------------------------------------------------------------//
//------------------- 3. Registro de informacion paises ------------------------//
//------------------------------------------------------------------------------//

void creacionArchivosPais(informacionPais *infoD)
{
	FILE *archivo; 
	string ruta;
	strcpy(ruta, ".\\InfoPaises\\");
	
	strcat(ruta, infoD->codigo);
	strcat(ruta, ".txt");
	
	archivo = fopen(ruta, "a+");
	fprintf(archivo,"%s;%s;%s;%s;", infoD->codigo, infoD->nombre, infoD->cantidadHabitantes, infoD->continente);
	fclose(archivo);
}

void lecturaDatosPais(informacionPais *infoD)
{	
	printf("\tIngrese el codigo del pais: ");
	gets(infoD->codigo);
	
	printf("\n\tIngrese el nombre del pais: ");
	gets(infoD->nombre);
	
	printf("\n\tIngrese la cantidad de habitantes: ");
	gets(infoD->cantidadHabitantes);
	
	printf("\n\tIngrese el continente al que pertenece: ");
	gets(infoD->continente);
}


void insercionCodigosPaises(informacionPais *infoD)
{
	FILE *archivo; 
	string ruta;
	strcpy(ruta, ".\\InfoPaises\\Codigos");
	strcat(ruta, ".txt");
	
	archivo = fopen(ruta, "a+");
	fprintf(archivo,"%s;", infoD->codigo);
	fclose(archivo);
}



void insertarDatosPais(ListaPaises *D, informacionPais infoD)
{
	lecturaDatosPais(&infoD);
	Nodo *n, *aux;

	if(D->inicio2 == NULL) //Valida si la lista esta vacia
	{
			D->inicio2 = (Nodo *) malloc(sizeof(Nodo));
			D->inicio2->dato3 = infoD;
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
		aux->siguiente->dato3 = infoD;
	}		
	creacionArchivosPais(&infoD);
	insercionCodigosPaises(&infoD);
	printf("\n");
	printf("\n");
	printf("\tLa informacion se ha registrado exitosamente");
	printf("\n");
	printf("\n");
}


//---------------------------------Eliminar------------------------------------//


void remove_word(char * text, char * word)
{
    int sizeText = strlen(text);
    int sizeWord = strlen(word);
    
    // Pointer to beginning of the word
    char * ptr = strstr(text, word);
    if(ptr)
    {
        //The position of the original text
        int pos = (ptr - text);

        // Increment the pointer to go in the end of the word to remove
        ptr = ptr + sizeWord;                
        
        // Search in the phrase and copy char per char
        int i;
        for(i = 0; i < strlen(ptr); i++)
        {
            text[pos + i] = ptr[i]; 
        }
        // Set the "new end" of the text               
        text[pos + i] = 0x00;      
    }   
}


void eliminarCodigoPais(string codigoPais){
	
	string ruta;
	strcpy(ruta, ".\\InfoPaises\\Codigos.txt");

    string text;
    string wordToRemove;
    
    // Word to remove
    strcpy(wordToRemove, codigoPais); 
    strcat(wordToRemove, ";"); 
    
    // Open for both reading and writing in binary mode - if exists overwritten
    FILE *fp = fopen(ruta, "a+");
    if (fp == NULL) {
        printf("\tError opening the file %s", ruta);
        return;
    }
    
    // Read the file
    fread(text, sizeof(char), 100, fp);
    fclose(fp);
	
    // Call the function to remove the word
    remove_word(text, wordToRemove);

    // Write the new text
    fp = fopen(ruta, "w+");	
    fprintf(fp, text);
    fclose(fp);
	
}


void eliminarInfoPais()
{
	FILE *archivo;
	string ruta;
	strcpy(ruta, ".\\InfoPaises\\");
	string codigoPais;
	
	printf("\tIngrese el codigo del pais el cual desea eliminar: ");
	gets(codigoPais);
	
	strcat(ruta, codigoPais);
	strcat(ruta, ".txt");
	
	remove(ruta);
	
	eliminarCodigoPais(codigoPais);

	//datosPaisTotales(infoD);
	printf("\n\tLa informacion del pais ha sido eliminada\n");
}


//----------------------------- Consultar Datos -----------------------------------//


void mostrarPaisesTotales( string lista[], int listSize )
{
	FILE *archivo = NULL; 
	
	int indice2 = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	string ruta;
	
	while( indice2 < listSize )
	{
	
		int indice = 0;
		strcpy(ruta, ".\\InfoPaises\\");
		strcat(ruta, lista[indice2]);
		strcat(ruta, ".txt");

		archivo = fopen(ruta, "a+");

		printf("\n\n ");
		if( archivo != NULL )
		{
			while(fgets(linea, 300, archivo))
			{
				token = strtok(linea, delimitador);
				while( token != NULL ) 
				{
					if(indice == 0)
					{
						printf("\t- Codigo: %s\n", token);
					}
					else if(indice == 1)
					{
						printf("\t - Nombre: %s\n", token);
					}
					else if(indice == 2)
					{
						printf("\t - Cantidad habitantes: %s\n", token);
					}	
					else if(indice == 3)
					{
						printf("\t - Continente: %s\n", token);
					}

					indice++;
					token = strtok(NULL, delimitador);
				}
			}
		indice2++;
		}	
	}
	fclose(archivo);
	printf("\n");
	printf("\n");
}


void extraerDatosPais()
{
	FILE *archivo = NULL; 

	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	string listaPaises[100];
	
	string ruta;
	strcpy(ruta, ".\\InfoPaises\\Codigos.txt");
	
	archivo = fopen(ruta, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy( listaPaises[indice], token );
      			indice++;
      			token = strtok( NULL, delimitador );
   			}
   			
		}
		mostrarPaisesTotales( listaPaises, indice );
	}
	fclose(archivo);
	
}


//--------------------------------- Modificar ------------------------------------//


void extraerListaInfoPaises(informacionPais *infoD, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;
	int respuesta;
	string nombre;
	string pais;
	string ciberataques;
	string espacio = " ";
	
	printf("\tQue desea modificar?\n\t1.Nombre del pais\n\t2.Cantidad de habitantes\n\t3.Continenete\n\t");
	scanf("%d", &respuesta);
	getchar();
	
	if(respuesta == 1)
	{
		printf("\tIngrese el nuevo nombre del pais: ");
		gets(nombre);
		strcpy(lista[1], nombre);
	}
	
	else if(respuesta == 2)
	{
		printf("\tIngrese la nueva cantidad de habitantes: ");
		gets(pais);
		strcpy(lista[2], pais);
	}
	else
	{
		printf("\tIngrese el nuevo continente: ");
		gets(ciberataques);
		strcpy(lista[3], ciberataques);
    } 
	
	string rutaAux;
	strcpy(rutaAux, ".\\InfoPaises\\");
	strcat(rutaAux,infoD->codigo);
	strcat(rutaAux, ".txt");
	archivoAux = fopen(rutaAux, "a+");
	
	fprintf( archivoAux,"%s;%s;%s;%s;", lista[0], lista[1], lista[2], lista[3] );
	fclose( archivoAux );

	printf("\n");
	printf("\tLa modificacion se realizo exitosamente");
	printf("\n");
	printf("\n");
}

void modificarInfoPais(informacionPais *infoD)
{
	FILE *archivo = NULL; 
	
	string listaPaises[100];
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	printf("\tIngrese el codigo del pais que desea modificar: ");
	gets(infoD->codigo);
	
	string ruta;
	strcpy(ruta, ".\\InfoPaises\\");
	strcat(ruta, infoD->codigo);
	strcat(ruta, ".txt");
	
	archivo = fopen(ruta, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador);
   			while( token != NULL ) 
			{
      			strcpy(listaPaises[indice], token);
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	remove(ruta);

	extraerListaInfoPaises(infoD, listaPaises);
}


//-----------------------  4. Gestion de informacion de ciberataques --------------------------------//

void archivosAtaques(informacionCiberataques *infoA)
{
	FILE *archivo; 
	string ruta;
	strcpy(ruta, ".\\InfoAtaques\\");
	
	strcat(ruta, infoA->paisOrigen);
	strcpy(infoA->tipoArchivo, ruta);
	strcat(infoA->tipoArchivo, ".txt");
	
	archivo = fopen(infoA->tipoArchivo, "a+");
	if(archivo == NULL)
	{
		fprintf(archivo,"%s;%s;%s;%s;%s;%s;", infoA->paisOrigen, infoA->paisDestino, infoA->tipoCiberataque, infoA->nombreCiberdelincuente, infoA->cantidadDatos, infoA->tiempo);
	}
	else
	{
		fprintf(archivo,"\n%s;%s;%s;%s;%s;%s;", infoA->paisOrigen, infoA->paisDestino, infoA->tipoCiberataque, infoA->nombreCiberdelincuente, infoA->cantidadDatos, infoA->tiempo);
	}
	fclose(archivo);
}

void insercionPaises(informacionCiberataques *infoA)
{
	FILE *archivo = NULL; 

	string listaPaises[100];
	infoA->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\InfoAtaques\\Paises");
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
      			strcpy(listaPaises[indice], token);
      			infoA->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	
	indice = 0;
	while(indice < infoA->tamano)
	{
		if(strcmp(listaPaises[indice], infoA->paisOrigen) == 0)
		{
			return;
		}
		indice++;
	}
	
	strcpy(ruta, ".\\InfoAtaques\\Paises");
	
	strcpy(infoA->tipoArchivo, ruta);
	strcat(infoA->tipoArchivo, ".txt");
	
	archivo = fopen(infoA->tipoArchivo, "a+");
	fprintf(archivo,"%s; ", infoA->paisOrigen);
}

void datosAtaque(informacionCiberataques *infoA)
{	
	printf("Ingrese el nombre del pais de origen: ");
	gets(infoA->paisOrigen);
	
	printf("\nIngrese el nombre del pais de destino: ");
	gets(infoA->paisDestino);
	
	printf("\nIngrese el tipo de ciberataque: ");
	gets(infoA->tipoCiberataque);
	
	printf("\nIngrese el nombre del ciberdelincuente que realizo el ataque: ");
	gets(infoA->nombreCiberdelincuente);

	printf("\nIngrese la cantidad de datos en gigabytes que fueron afectados: ");
	gets(infoA->cantidadDatos);

	printf("\nIngrese el tiempo en segundos que tardo el ciberataque: ");
	gets(infoA->tiempo);

	archivosAtaques(infoA);
	insercionPaises(infoA);
	
	printf("\n");
	printf("La informacion se registro exitosamente");
}

bool vacio()
{
	if(inicioG == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

vertice *getVertice(string nombre)
{
	vertice *aux;
	aux = inicioG;

	while(aux != NULL)
	{
		if(strcmp(aux->nombre, nombre) == 0)
		{
			return aux;
		}
		aux = aux->siguiente;
	}
	return NULL;
}

void insertarArista(informacionCiberataques infoA, string lista[])
{
	FILE *archivo = NULL; 

	string listaPaises[100];
	string listaInfo[100];
	int indice = 0;
	char linea[300];
	char *delimitador1 = "\n";
	char *delimitador2 = ";";
	char *token = NULL;
	string ruta;
	
	while(indice < infoA.tamano)
	{
		int tamanoInfo = 0;
		int indice2= 0;
		strcpy(ruta, ".\\InfoAtaques\\");
		strcat(ruta, lista[indice]);
		strcpy(infoA.tipoArchivo, ruta);
		strcat(infoA.tipoArchivo, ".txt");

		archivo = fopen(infoA.tipoArchivo, "a+");

		if(archivo)
		{
			while(fgets(linea, 300, archivo))
			{
				token = strtok(linea, delimitador1);
				while( token != NULL ) 
				{
					strcpy(listaPaises[indice2], token);
					tamanoInfo++;
					indice2++;

					token = strtok(NULL, delimitador1);
				}
			}
		}
		fclose(archivo);

		int indice3 = 0;

		while(indice3 < tamanoInfo)
		{
			indice2 = 0;
			token = strtok(listaPaises[indice3], delimitador2);
			while( token != NULL ) 
			{
				strcpy(listaInfo[indice2], token);
				indice2++;

				token = strtok(NULL, delimitador2);
			}

			vertice *origen = getVertice(listaInfo[0]);
			vertice *destino = getVertice(listaInfo[1]);
			strcpy(infoA.tipoCiberataque, listaInfo[2]);
			strcpy(infoA.nombreCiberdelincuente, listaInfo[3]);
			strcpy(infoA.cantidadDatos, listaInfo[4]);
			strcpy(infoA.tiempo, listaInfo[5]);

			arista *nueva = (arista *)malloc(sizeof(arista));
			nueva->siguiente = NULL;
			nueva->ady = NULL;

			arista *aux;
			aux = origen->ady;
			if(aux == NULL)
			{
				origen->ady = nueva;
				nueva->ady = destino;
				nueva->dato3 = infoA;
			}
			else
			{
				while(aux->siguiente != NULL)
				{
					aux = aux->siguiente;
				}
				aux->siguiente = nueva;
				nueva->ady = destino;
				nueva->dato3 = infoA;
			}
			indice3++;
		}
		indice++;
	}	
}

void insertarVertice(informacionCiberataques *infoA, string listaPaises[])
{
	int indice = 0;

	while(indice < infoA->tamano)
	{
		vertice *nuevo = (vertice *)malloc(sizeof(vertice));
		strcpy(nuevo->nombre, listaPaises[indice]);
		nuevo->siguiente = NULL;
		nuevo->ady = NULL;

		if(vacio())
		{
			inicioG = nuevo;
		}
		else
		{
			vertice *aux;
			aux = inicioG;
			while(aux->siguiente != NULL)
			{
				aux = aux->siguiente;
			}
			aux->siguiente = nuevo;
		}
		indice++;
	}	
	insertarArista(*infoA, listaPaises);
}

void extraerListaPaises(informacionCiberataques *infoA)
{
	FILE *archivo = NULL; 

	string listaPaises[100];
	infoA->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\InfoAtaques\\Paises");
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
      			strcpy(listaPaises[indice], token);
      			infoA->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador);
   			}
		}
	}
	fclose(archivo);
	insertarVertice(infoA, listaPaises);
}

void listaAdyacencia()
{
	vertice *vertAux;
	arista *arisAux;
	vertAux = inicioG;

	printf("Informacion de todos los ataques: \n");
	printf("\n");

	while(vertAux != NULL)
	{
		arisAux = vertAux->ady;

		if(arisAux == NULL)
		{
			vertAux = vertAux->siguiente;
		}
		else
		{
			printf("Ataques de %s:\n", vertAux->nombre);
			printf("\n");

			while(arisAux != NULL)
			{
				printf(" Pais de destino:       %s\n", arisAux->ady->nombre);
				printf(" Tipo de ciberataque:   %s\n", arisAux->dato3.tipoCiberataque);
				printf(" Ciberdelincuente:      %s\n", arisAux->dato3.nombreCiberdelincuente);
				printf(" Cantidad de datos:     %s GB\n", arisAux->dato3.cantidadDatos);
				printf(" Tiempo:                %s segundos\n", arisAux->dato3.tiempo);
				printf("\n");
				arisAux = arisAux->siguiente;
			}
			printf("________________________________________________________________");
			printf("\n");
			vertAux = vertAux->siguiente;
			printf("\n");
		}
	}
}

//-----------------------  Eliminar un ataque --------------------------------//

void listaEliminarLinea(informacionCiberataques *infoA, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;
	int indice2 = 0;
	int indice3;
	string listaA[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string rutaAux;
	strcpy(rutaAux, ".\\infoAtaques\\");
	strcat(rutaAux,infoA->paisOrigen);
	strcpy(infoA->tipoArchivo, rutaAux);
	strcat(infoA->tipoArchivo, ".txt");
	archivoAux = fopen(infoA->tipoArchivo, "a+");

	while(indice < infoA->tamano)
	{
		indice2 = 0;
		token = strtok(lista[indice], delimitador);
		while( token != NULL ) 
		{
			strcpy(listaA[indice2], token);
			indice2++;

			token = strtok(NULL, delimitador);
		}

		if(strcmp(listaA[1], infoA->paisDestino) != 0)
		{
			indice3 = 0;
			while(indice3 < 6)
			{
				if(indice3 == 5)
				{
					fprintf(archivoAux,"%s;\n", listaA[indice3]);	
				}
				else
				{
					fprintf(archivoAux,"%s;", listaA[indice3]);
				}
				indice3++;
			}
		}	
		indice++;
	}	
	
	printf("\n");
	printf("La eliminacion se realizo exitosamente");
	printf("\n");
	printf("\n");
	exit(-1);
}

void eliminarUnAtaque(informacionCiberataques *infoA)
{
	FILE *archivo = NULL; 
	
	string listaAtaques[100];
	infoA->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador1 = "\n";
	char *delimitador2 = ";";
	char *token = NULL;
	
	printf("Ingrese el pais de origen y el pais de destino del ataque que desea eliminar: \n");
	printf("\n");
	printf("Pais de origen: ");
	gets(infoA->paisOrigen);
	printf("\n");
	printf("Pais de destino: ");
	gets(infoA->paisDestino);
	
	string ruta;
	strcpy(ruta, ".\\infoAtaques\\");
	strcat(ruta, infoA->paisOrigen);
	strcpy(infoA->tipoArchivo, ruta);
	strcat(infoA->tipoArchivo, ".txt");
	
	archivo = fopen(infoA->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador1);
   			while( token != NULL ) 
			{
      			strcpy(listaAtaques[indice], token);
      			infoA->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador1);
   			}
		}
	}
	fclose(archivo);
	remove(infoA->tipoArchivo);

	listaEliminarLinea(infoA, listaAtaques);
}

//-----------------------  Eliminar un pais --------------------------------//

void eliminarPais(informacionCiberataques *infoA, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;

	string rutaAux;
	strcpy(rutaAux, ".\\infoAtaques\\Paises");
	strcpy(infoA->tipoArchivo, rutaAux);
	strcat(infoA->tipoArchivo, ".txt");
	archivoAux = fopen(infoA->tipoArchivo, "a+");
	
	while(indice < infoA->tamano)
	{	
		if(strcmp(lista[indice], infoA->paisOrigen) == 0)
		{
			strcpy(lista[indice], "");
		}
		else if(indice == (infoA->tamano)-1)
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

void archivoAtaquesTotales(informacionCiberataques *infoA)
{
	FILE *archivo = NULL; 
	
	string listaAtaques[100];
	infoA->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador = ";";
	char *token = NULL;
	
	string ruta;
	strcpy(ruta, ".\\infoAtaques\\Paises");
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

	eliminarPais(infoA, listaAtaques);
}

void eliminarInfoA(informacionCiberataques *infoA)
{
	FILE *archivo;
	string ruta;
	strcpy(ruta, ".\\infoAtaques\\");
	
	printf("Ingrese el nombre del pais al cual desea eliminar la informacion: ");
	gets(infoA->paisOrigen);
	
	strcat(ruta, infoA->paisOrigen);
	strcpy(infoA->tipoArchivo, ruta);
	strcat(infoA->tipoArchivo, ".txt");
	
	archivo = fopen(infoA->tipoArchivo, "w");

	fclose(archivo);
	
	remove(infoA->tipoArchivo);

	archivoAtaquesTotales(infoA);
	printf("\nLa informacion ha sido eliminada exitosamente\n");
	exit(-1);
}

//-----------------------  Modificar informacion --------------------------------//

void listaAtaquesEspaciado(informacionCiberataques *infoA, string lista[])
{	
	FILE *archivoAux;
	
	int indice = 0;
	int indice2 = 0;
	int indice3;
	int respuesta;
	string listaA[300];
	string tipoCiberataque;
	string ciberdelincuente;
	string cantidadDatos;
	string tiempo;
	char *delimitador = ";";
	char *token = NULL;
	
	string rutaAux;
	strcpy(rutaAux, ".\\infoAtaques\\");
	strcat(rutaAux,infoA->paisOrigen);
	strcpy(infoA->tipoArchivo, rutaAux);
	strcat(infoA->tipoArchivo, ".txt");
	archivoAux = fopen(infoA->tipoArchivo, "a+");

	printf("\n");
	printf("Que desea modificar?\n1.Tipo de ciberataque\n2.Nombre del ciberdelincuente\n3.Cantidad de datos\n4.Tiempo que duro el ciberataque\n");
	scanf("%d", &respuesta);
	getchar();

	while(indice < infoA->tamano)
	{
		indice2 = 0;
		token = strtok(lista[indice], delimitador);
		while( token != NULL ) 
		{
			strcpy(listaA[indice2], token);
			indice2++;

			token = strtok(NULL, delimitador);
		}

		if(strcmp(listaA[1], infoA->paisDestino) == 0)
		{
			if(respuesta == 1)
			{
				printf("Ingrese el tipo de ciberataque: ");
				gets(tipoCiberataque);
				strcpy(listaA[2], tipoCiberataque);
			}

			else if(respuesta == 2)
			{
				printf("Ingrese el nombre del ciberdelincuente: ");
				gets(ciberdelincuente);
				strcpy(listaA[3], ciberdelincuente);
			}
			else if(respuesta == 3)
			{
				printf("Ingrese la cantidad de datos: ");
				gets(cantidadDatos);
				strcpy(listaA[4], cantidadDatos);
			} 
			else
			{
				printf("Ingrese el tiempo: ");
				gets(cantidadDatos);
				strcpy(listaA[5], tiempo);
			}
		}
		
		indice3 = 0;
		while(indice3 < 6)
		{
			if(indice3 == 5)
			{
				fprintf(archivoAux,"%s;\n", listaA[indice3]);	
			}
			else
			{
				fprintf(archivoAux,"%s;", listaA[indice3]);
			}
			indice3++;
		}
		indice++;
	}	
	
	printf("\n");
	printf("La modificacion se realizo exitosamente");
	printf("\n");
	printf("\n");
	exit(-1);
}

void modificarAtaques(informacionCiberataques *infoA)
{
	FILE *archivo = NULL; 
	
	string listaAtaques[100];
	infoA->tamano = 0;
	int indice = 0;
	char linea[300];
	char *delimitador1 = "\n";
	char *delimitador2 = ";";
	char *token = NULL;
	
	printf("Ingrese el pais de origen y el pais de destino del ataque al cual desea modificar la informacion: \n");
	printf("\n");
	printf("Pais de origen: ");
	gets(infoA->paisOrigen);
	printf("\n");
	printf("Pais de destino: ");
	gets(infoA->paisDestino);
	
	string ruta;
	strcpy(ruta, ".\\infoAtaques\\");
	strcat(ruta, infoA->paisOrigen);
	strcpy(infoA->tipoArchivo, ruta);
	strcat(infoA->tipoArchivo, ".txt");
	
	archivo = fopen(infoA->tipoArchivo, "a+");
	
	if(archivo)
	{
		while(fgets(linea, 300, archivo))
		{
   			token = strtok(linea, delimitador1);
   			while( token != NULL ) 
			{
      			strcpy(listaAtaques[indice], token);
      			infoA->tamano++;
      			indice++;
    
      			token = strtok(NULL, delimitador1);
   			}
		}
	}
	fclose(archivo);
	remove(infoA->tipoArchivo);

	listaAtaquesEspaciado(infoA, listaAtaques);
}

//-----------------------  5. Registro de mensaje de seguridad de notificacion de ciberataque --------------------------------//

bool existeCaracterCadena(string cadena, char caracter)
{
	int tamano = strlen(cadena);
	
    //if(strcpy(cadena, " ") == 0):
       //return false
    int indice = 0;
    
    while(indice < tamano)
    {
    	if(cadena[indice] == caracter)
    	{
    		return true;
		}
        indice++;
	}
    return false;
}

int determinarPosicionLetraCadena(string cadena, char letra, int posicion)
{
	int indice = 0;
	
    while(indice < 27)
    {
    	if(letra == cadena[indice])
    	{
    		return posicion;
		}
	    posicion++;
	    indice++;
	}
	return false;
}

void cifradoCesar()
{
	string mensaje;
	char letra;
	int posicion;
	int indice = 0;
	string alfabetoValido;
	string alfabetoCifrado;
	string cadenaCifrada;
    strcpy(alfabetoValido, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    strcpy(alfabetoCifrado, "DEFGHIJKLMNOPQRSTUVWXYZABC");
    
    printf("Ingrese un mensaje: ");
    gets(mensaje);
    
    int tamano = strlen(mensaje);

    while(indice < tamano)
    {
        letra = mensaje[indice];
        letra = toupper(letra);
        
        if((existeCaracterCadena(alfabetoValido, letra)) == true)
        {
        	posicion = determinarPosicionLetraCadena(alfabetoValido, letra, 0);
        	char letraCifrada[2];
			letraCifrada[0] = alfabetoCifrado[posicion];
        	letraCifrada[1] = '\0';
            strcat(cadenaCifrada, letraCifrada);
		}
        else
        {
        	char letraSinCifrar[2];
			letraSinCifrar[0] = mensaje[indice];
			letraSinCifrar[1] = '\0';
        	strcat(cadenaCifrada, letraSinCifrar);
		}
		indice++;
	}
	printf("\n");
    printf("Cadena cifrada: %s", cadenaCifrada);
}

//-----------------------  Creacion del menu --------------------------------//

void administrarInfoAtaques()
{
	informacionCiberataques ataques;

	int activadorBucle2 = 1;
	int opcionElegidaSubmenu;
	printf(" \n");

	while(activadorBucle2 == 1)
	{
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\n");
		printf("\t__________________________________________________\n");
		printf("\n");
		printf("\tAdministrar informacion de los ciberataques       \n");
		printf("\t__________________________________________________\n");
		printf(" \n");
		printf(" \n");
		printf("\t1-Registrar un ciberataque\n");
		printf("\t2-Modificar informacion\n");
		printf("\t3-Eliminar informacion de un ciberataque\n");
		printf("\t4-Eliminar informacion de un pais\n");
		printf("\t5-Consultar informacion\n");
		printf("\t6-Regresar al menu principal\n");
		printf("\n");
		printf("\n");
		printf("\tSeleccione una de las funciones disponibles: ");
		scanf("%d", &opcionElegidaSubmenu);
		getchar();
		printf("\n");
		printf("\n");
		
		if(opcionElegidaSubmenu>6)
		{
			printf("\tLa opcion elegida no es valida, elija otra opcion\n");
				printf(" \n");
				printf(" \n");		
		}

		switch(opcionElegidaSubmenu)
		{
			case 1: datosAtaque(&ataques);
			break;
			case 2: modificarAtaques(&ataques);
			break;
			break;
			case 3: eliminarUnAtaque(&ataques);
			break;
			case 4: eliminarInfoA(&ataques);
			break;
			case 5: extraerListaPaises(&ataques);
			        listaAdyacencia();
			case 6: printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\n");
					printf("\n");
					menu();
			break;
		}
	}		
}

void administrarInfoPaises()
{
	
	ListaPaises *P;
    P = lista3();
    informacionPais paises;
	
	int activadorBucle2 = 1;
	int opcionElegidaSubmenu;
	printf(" \n");
	
	while(activadorBucle2 == 1)
	{
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\n");
		printf("\t____________________________________________________________\n");
		printf("\n");
		printf("\t          Administrar informacion de los paises             \n");
		printf("\t____________________________________________________________\n");
		printf(" \n");
		printf(" \n");
		printf("\t1-Registrar un pais\n");
		printf("\t2-Modificar informacion\n");
		printf("\t3-Eliminar informacion\n");
		printf("\t4-Consultar informacion\n");
		printf("\t5-Regresar al menu principal\n");
		printf("\n");
		printf("\n");
		printf("\tSeleccione una de las funciones disponibles: ");
		scanf( "%d", &opcionElegidaSubmenu);
		getchar();
		printf("\n");
		printf("\n");
		
		if(opcionElegidaSubmenu>6)
		{
			printf("\tLa opcion elegida no es valida, elija otra opcion\n");
				printf(" \n");
				printf(" \n");		
		}

		switch(opcionElegidaSubmenu)
		{
			
			case 1: 
				//printf("Registrar");
				insertarDatosPais(P, paises);
				break;
			case 2: 
				//printf("Modificar");
				modificarInfoPais(&paises);
				break;
			case 3: 
				//printf("Eliminar");
				eliminarInfoPais();
				break;
			case 4: 
				//printf("Consultar");
				extraerDatosPais(&paises);
				break;
			case 5: printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\n");
					printf("\n");
					menu();
			break;
		}
		
		//insertarDatosPais(P, paises);
		//eliminarInfoPais();
		//extraerDatosPais(&paises);
		//modificarInfoPais(&paises);
			
	}		
}

void administrarInfoDelincuentes()
{
	ListaDelincuentes *D;
    D = lista2();
    informacionCiberdelincuente delincuentes;

	int activadorBucle2 = 1;
	int opcionElegidaSubmenu;
	printf(" \n");

	while(activadorBucle2 == 1)
	{
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\n");
		printf("\t____________________________________________________________\n");
		printf("\t\n");
		printf("\t       Administrar informacion de ciberdelincuentes         \n");
		printf("\t____________________________________________________________\n");
		printf("\t \n");
		printf("\t \n");
		printf("\t1-Registrar ciberdelincuente\n");
		printf("\t2-Modificar informacion\n");
		printf("\t3-Eliminar informacion\n");
		printf("\t4-Consultar informacion\n");
		printf("\t5-Regresar al menu principal\n");
		printf("\n");
		printf("\n");
		printf("\tSeleccione una de las funciones disponibles: ");
		scanf( "%d", &opcionElegidaSubmenu);
		getchar();
		printf("\n");
		printf("\n");
		
		if(opcionElegidaSubmenu>6)
		{
			printf("\tLa opcion elegida no es valida, elija otra opcion\n");
				printf(" \n");
				printf(" \n");		
		}

		switch(opcionElegidaSubmenu)
		{
			case 1: insertarDatosDelincuente(D, delincuentes);
			break;
			case 2: modificarInfoD(&delincuentes);
			break;
			case 3: eliminarCiberDelincuente(&delincuentes);
			break;
			case 4: extraerDatosDelincuentes(&delincuentes);
			break;
			case 5: printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\n");
					printf("\n");
					menu();
			break;
		}
	}		
}

void administrarInfoTipos()
{
	ListaAtaques *A;
    A = lista1();
    tipoCiberataque tipos;

	int activadorBucle2 = 1;
	int opcionElegidaSubmenu;
	printf(" \n");

	while(activadorBucle2 == 1)
	{
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\t\t.\n");
		printf("\n");
		printf("\t____________________________________________\n");
		printf("\t\n");
		printf("\t  Administrar tipos de ciberataques      \n");
		printf("\t_____________________________________________\n");
		printf("\t \n");
		printf("\t \n");
		printf("\t1-Registrar tipo de ciberataque\n");
		printf("\t2-Modificar informacion\n");
		printf("\t3-Eliminar informacion\n");
		printf("\t4-Consultar informacion\n");
		printf("\t5-Regresar al men%c principal\n",163);
		printf("\t\n");
		printf("\t\n");
		printf("\tSeleccione una de las funciones disponibles: ");
		scanf( "%d", &opcionElegidaSubmenu);
		getchar();
		printf("\n");
		printf("\n");
		
		if(opcionElegidaSubmenu>6)
		{
			printf("\tLa opcion elegida no es valida, elija otra opcion\n");
				printf(" \n");
				printf(" \n");		
		}

		switch(opcionElegidaSubmenu)
		{
			
			case 1: insertarAtaque(A, tipos);
			break;
			case 2: modificarInfoV(&tipos);
			break;
			case 3: eliminarCiberataque(&tipos);
			break;
			case 4: extraerDatosAtaques(&tipos);
			break;
			case 5: printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\t\t.\n");
					printf("\n");
					printf("\n");
			        menu();
			break;
		}
	}		
}

void menu()
{
	int activadorBucle=1;
	int opcionElegidaPrincipal;

	while(activadorBucle==1)
	{
		printf("\t**************************************************\n\n");
		printf("\t*                 CIBERSEGURIDAD                 *\n");     
		printf("\t*                                                *\n");         
		printf("\t*                 MENU PRINCIPAL                 *\n\n");
		printf("\t**************************************************\n");
		printf(" \n");
		printf(" \n");
		printf("\t1-Gestion de informacion sobre tipos de ciberataque\n");
		printf("\t2-Gestion de informacion sobre ciberdelincuentes\n");
		printf("\t3-Gestion de informacion de paises\n");
		printf("\t4-Gestion de informacion de ciberataques\n");
		printf("\t5-Registro de mensaje de seguridad\n");
		printf("\t6-Simulacion de ciberataques\n");
		printf("\t7-Obtener rutas de ciberataques\n");
		printf("\t8-Analisis de datos\n");
		printf("\t9-Salir\n");
		printf(" \n");
		printf(" \n");
		printf("\tSeleccione una de las funciones disponibles: ");
		scanf( "%d", &opcionElegidaPrincipal);
		getchar();
		printf(" \n");
		printf(" \n");

		if((opcionElegidaPrincipal>9)|| (opcionElegidaPrincipal<1))
		{
			printf("----La opcion elegida no es valida, elija otra opcion----\n");
			printf(" \n");
			printf(" \n");
			printf(" \n");
		}
		switch(opcionElegidaPrincipal)
		{	
			case 1: administrarInfoTipos();
			break;
			
			case 2: administrarInfoDelincuentes();
			break;
			
			case 3: administrarInfoPaises();
			break;
			
			case 4: administrarInfoAtaques();
			break;

			case 5: printf("Funcion 5: Registro de mensajes de seguridad");
			break;
			
			case 6: printf("Funcion 6: Simulacion de ciberataques");
			break;

			case 7: printf("Funcion 7: Obtener rutas de ciberataques");
			break;

			case 8: printf("Funcion 8: Analisis de datos\n");
			break;

			case 9: activadorBucle=0;
			exit(-1);
		}
	}
}

int main()
{
    ListaAtaques *A;
    A = lista1();
    tipoCiberataque tipos;

    ListaDelincuentes *D;
    D = lista2();
    informacionCiberdelincuente delincuentes;

	informacionCiberataques ataques;
	
	ListaPaises *P;
    P = lista3();
    informacionPais paises;

    //insertarAtaque(A, tipos);
    //eliminarCiberataque(&tipos);
    //modificarInfoV(&tipos);
	//extraerDatosAtaques(&tipos);

    //insertarDatosDelincuente(D, delincuentes);
    //eliminarCiberDelincuente(&delincuentes);
    //modificarInfoD(&delincuentes);
	//extraerDatosDelincuentes(&delincuentes);

	//datosAtaque(&ataques);
	//extraerListaPaises(&ataques);
	//listaAdyacencia();
	//eliminarInfoA(&ataques);
	//modificarAtaques(&ataques);
	//eliminarUnAtaque(&ataques);

	//cifradoCesar();
	
	menu();

    return 0;
}
