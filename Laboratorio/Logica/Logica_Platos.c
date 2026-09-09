#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "..\Interfaz\Interfaz_Platos.h"
#include "..\Interfaz\Interfaz_Pedidos.h"
#include "..\Logica\Logica_Pedidos.h"
#include "..\Logica\Logica_Platos.h"
#include "..\Estructura\Estructuras.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
void convertirminus(char aux[]) // funcion que se encarga de convertir las cadenas de caracteres a minuscula
{
    for (int i = 0; aux[i] != '\0'; i++)
    {
        aux[i] = tolower(aux[i]); // convierte a minúscula
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int comprobacionNum(float precio) // funcion que se encarga de comprobar si todos los valores numericos son mayores a 0 para asi no tener probleas
{
    if (precio > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int verificarPlato(struct Plato platos[], int cantPlatos, char nombre[100]) // verifica si ya hay un plato guardado con ese nombre, sirve para agregar un plato nuevo
{
    for (int i = 0; i < cantPlatos; i++)
    {
        if (strcasecmp(platos[i].nombre, nombre) == 0) // compara dos cadenas sin importar si estas tengan manuscula o mayuscula
        {
            return 1;
        }
    }
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void actualizarStock(struct Plato *plato, int cantidadVendida) // actualiza el stock de un plato
{
    int aux;
    aux = (plato->stock);
    (plato->stock) = aux - cantidadVendida; // resta la cantidad de porciones que pidio el cliente con la cantidad de porciones que habia
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int verificarStock(struct Plato platos[], int op, int cantidadsolicita, int cantidad) // verifica el stock de un plato
{
    if (cantidadsolicita < 0)
    {
        return 1;
    } 
    else if (cantidadsolicita > platos[op].stock) // si cantidad solicitada es menor a platos
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void registrarPlatoLogica(struct Plato *platos, char nombre[100], float precio, int stock, int id) // registra un plato
{
    // guarda los datos ingresados en la interfaz y los guarda en el arreglo
    strcpy((platos->nombre), nombre);
    (platos->precio) = precio;
    (platos->stock) = stock;
    (platos->id) = id;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
struct Plato *MostrarCartaLogica(struct Plato platos[], int cantPlatos, int *cont)
{
    if (cont) // si cont == 1
    {
        *cont = 0; // cont = 0, es decir que se reinicia el contador
    }

    if (cantPlatos <= 0) // si no hay platos registrados
    {
        return NULL; // retorna nulo
    }

    int disponibleCount = 0;             // crea una variable
    for (int i = 0; i < cantPlatos; i++) // recorre un for de i hastaa cantPlatos
    {
        if (platos[i].stock > 0) // si el stock del plato es mayor a 0
        {
            disponibleCount++; // suma 1
        }
    }

    if (disponibleCount == 0) // si el contador = 0 retorna nulosponibleCount = a 0 retorna null
    {
        return NULL;
    }

    // reservo memoria dinamica.
    struct Plato *disponibles = malloc(sizeof(struct Plato) * (size_t)disponibleCount); // reserva un espacio en memoria y multiploca el tamaño del struct plato * el tamaño de disponibleCount

    if (disponibles == NULL)
    { // verifica si disponibles es nulo
        printf("error al asignar memoria\n");
        exit(1);
    }
    if (!disponibles) // disponible = 0 es verdadero significa que no hay platos disponibles
    {
        // se reinicia el contador
        if (cont)
        {
            *cont = 0;
        }
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < cantPlatos; i++) // recorre el for de i hasta cantidadPlatos
    {
        if (platos[i].stock > 0) // si platos menor a 0
        {
            disponibles[j++] = platos[i]; // copia del struct
        }
    }

    if (cont) // cont == 1
    {
        *cont = disponibleCount; // se le pasa al puntero la cantidad de platos disponibles
    }
    return disponibles;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

void importarPlatos(struct Plato platos[], int *cantPlatos) // carga platos al archivos
{
    struct Plato plato;
    char cadena[100];
    FILE *archivo;

    archivo = fopen("..\\Archivos\\Platos.txt", "r"); // Archivo de texto a leer
    //.. es para retroceder a la carpeta anterior, facilitando la busqueda del archivo en otra carpeta
    if (archivo == NULL)
    {
        return;
    }

    while (fgets(cadena, sizeof(cadena), archivo) != NULL) // lee linea por linea dentro del archivo que pasa a cadena
    {

        cadena[strcspn(cadena, "\n")] = 0; // Elimina salto de linea
        memset(&plato, 0, sizeof(plato));  // Limpiar la estructura antes de cargar nuevos datos

        int campo = 0;
        char *tok = strtok(cadena, ","); // tok permite delimitar con la coma puesto que es lo que permite separarlos campos en los platos

        while (tok != NULL)
        {
            switch (campo)
            {
            case 0:
                plato.id = (int)strtol(tok, NULL, 10); // Convierte una cadena a un número entero (long).
                break;
            case 1:
                strncpy(plato.nombre, tok, sizeof(plato.nombre) - 1); // Copia una cadena de caracteres (tok) dentro del campo nombre del struct.
                plato.nombre[sizeof(plato.nombre) - 1] = '\0';        // Copia texto en nombre (con límite seguro)
                // Copia hasta un carácter menos que el tamaño total para dejar espacio al \0
                break;
            case 2:
                plato.precio = (float)strtof(tok, NULL); // Convierte una cadena a número decimal (float). debido aque el archivo esta en texto
                // Convierte el texto del tercer campo (por ejemplo "2500.50") a un número flotante.
                break;
            case 3:
                plato.stock = (int)strtol(tok, NULL, 10); // convierte numero del archivo a base decimal 10
                break;
            default:
                break;
            }
            campo++;
            tok = strtok(NULL, ",");
        }

        platos[*cantPlatos] = plato;
        *cantPlatos = (*cantPlatos + 1); // se va incrementando la cantidad de platos
    }
    fclose(archivo);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void exportarPlatos(struct Plato platos[], int cantPlatos)
{
    FILE *archivo;                                    // puntero file que permite manejar el archivo
    archivo = fopen("..\\Archivos\\Platos.txt", "w"); // abre el archivo
    for (int i = 0; i < cantPlatos; i++)              // utilza for de i hasta cantPedidos
    {
        fprintf(archivo, "%i,%s,%f,%i\n", platos[i].id, platos[i].nombre, platos[i].precio, platos[i].stock);
    }
    fclose(archivo);
}