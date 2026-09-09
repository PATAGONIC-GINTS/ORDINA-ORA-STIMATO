#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "..\Interfaz\Interfaz_Platos.h"
#include "..\Interfaz\Interfaz_Pedidos.h"
#include "..\Logica\Logica_Platos.h"
#include "..\Logica\Logica_Pedidos.h"
#include "..\Estructura\Estructuras.h"
#include "Interfaz_Registro.h"
#include "..\Logica\Logica_Registro.h"
#include "..\Logica\estetica.h"

void registro(struct Plato platos[], struct Pedido pedidos[], int cantPedidos) // imprime el reporte general del ida
{
    int aux = 0;
    int indice = 0;
    printf("++-------------------------------------------------------------------------------++\n");
    printf("|| %s||\n", "REPORTE GENERAL DEL DIA");
    printf("|| El total de pedidos realizado es de: %i\n", cantPedidos);
    printf("|| La cantidad de pedidos activos es de: %i\n", contarPedidos(pedidos, cantPedidos, 1));
    printf("|| La cantidad de pedidos completados es de: %i\n", contarPedidos(pedidos, cantPedidos, 0));
    printf("|| El total recaudado del dia es de: %.2f\n", platita(pedidos, cantPedidos));
    aux = elMasPedido(pedidos, cantPedidos, &indice); // guarda la funcion elMasPedido en aux
    printf("|| El plato mas pedido es: %s con una cantidad de %i veces\n", platos[indice].nombre, aux);
    printf("|| ");
    clienteMayorGastoInterfaz(pedidos, cantPedidos); // llama a clienteMayorInterfaz
    printf("|| Precione cualquier tecla para regresar al menu principal. . .\n");
    printf("++-------------------------------------------------------------------------------++\n");
}

// Muestra en pantalla el cliente con mayor gasto
void clienteMayorGastoInterfaz(struct Pedido pedidos[], int cantPedidos) // muestra el cliente que tiene el mayor gasto
{
    char clienteMax[100];
    float gastoMax;

    clienteMayorGastoLogica(pedidos, cantPedidos, clienteMax, &gastoMax); // llama a la funcion clienteMayorGastoLogica
    printf("||Cliente con mayor gasto del dia:");
    printf("||Cliente: %s Gasto total: $%.2f\n", clienteMax, gastoMax); // muestra en pantalla al cliente(su nombre) con mas gasto
    printf("++-------------------------------------------------------------------------------++\n");
}