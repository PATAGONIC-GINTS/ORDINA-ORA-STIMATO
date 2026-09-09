#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "..\interfaz\Interfaz_Platos.h"
#include "..\interfaz\Interfaz_Pedidos.h"
#include "..\Logica\Logica_Platos.h"
#include "..\Logica\Logica_Pedidos.h"
#include "..\Estructura\Estructuras.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

void mostrarCartaInterfaz(struct Plato platos[], int cantPlatos)
{
    int cont = 0;
    struct Plato *disponibles = MostrarCartaLogica(platos, cantPlatos, &cont); // crea un espacio de memoria y guarda la funcion MostrarCartaLogica
    for (int i = 0; i < cont; i++)                                             // recorre el for hasta cont
    {
        // imprime la carta
        printf("++------------------------------------------------------------------------++\n");
        printf("||%i) %s (%i unidades restantes) : $%.2f\n", disponibles[i].id, disponibles[i].nombre, disponibles[i].stock, disponibles[i].precio);
    }
        printf("++------------------------------------------------------------------------++\n");
    free(disponibles); // libera memoria
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void registrarPlatoInterfaz(struct Plato platos[], int *cantPlatos)
{
    char aux[100];
    int stock, id;
    float precio;
    int temp1, temp2;
    printf("++----------------------------------------++\n");
    printf("Ingrese los datos del nuevo plato\n");
    printf("Ingrese el nombre:\n");
    getchar();                      // espera que el usuario ingrese un carácter. Una vez que se presiona una tecla, el carácter se lee y se devuelve.
    fgets(aux, sizeof(aux), stdin); // lee el nombre ingresado
    aux[strcspn(aux, "\n")] = 0;    // quita el salto de linea del fgets
    convertirminus(aux);            // convierte en minuscula para tener siempre un mismo formato y no tener problemas al comparar

    if (verificarPlato(platos, *cantPlatos, aux) == 1) // llama a verificarPlato y verifica con "1"
    {
        printf("El plato ya existe en el menu\n");
        return;
    }

    do // ingresa el precio del plato y verfica que sea mayor a 0
    {
        temp1 = 0;
        printf("Ingrese el precio del plato\n");
        scanf("%f", &precio);
        comprobacionNum(precio);          // llama a la funcion comprobacionNum
        if (comprobacionNum(precio) == 0) // si comprobacionNum = 0
        {
            printf("Error, ingreso un valor invalido. Debe poner un precio mayor a 0\n");
            temp1 = 1;
        }

    } while (temp1 == 1); // mientras temp1 sea igual a 1 queda en bucle
    // ingresa el stock del plato  verifica que sea mayor a 0
    do
    {
        temp2 = 0;
        printf("Ingrese el stock del plato\n");
        scanf("%i", &stock);
        comprobacionNum(stock);
        if (comprobacionNum(stock) == 0)
        {
            printf("Error, ingreso un valor invalido. Debe poner un stock mayor a 0\n");
            scanf("%i", &stock);

            temp2 = 1;
        }
    } while (temp2 == 1);

    id = *cantPlatos;                                                   // guarda en id un puntero
    registrarPlatoLogica(&platos[*cantPlatos], aux, precio, stock, id); // llama a regustrarPlatoLogica
    *cantPlatos = (*cantPlatos + 1);                                    // contador de platos (id)
    printf("++----------------------------------------++\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////
