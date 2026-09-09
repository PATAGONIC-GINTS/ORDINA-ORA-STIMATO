#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "..\Interfaz\Interfaz_Platos.h"
#include "..\Interfaz\Interfaz_Pedidos.h"
#include "..\Logica\Logica_Pedidos.h"
#include "..\Logica\Logica_Platos.h"
#include "Logica_Registro.h"
#include "..\Estructura\Estructuras.h"
//////////////////////////////////////////////////////////////////////////////////
float platita(struct Pedido pedidos[], int cantpedidos)
{
    float contador = 0;

    for (int i = 0; i < cantpedidos; i++) // recorre hasta cantPedidos
    {
        contador = pedidos[i].total + contador; // el contador va a ser igual a la suma de todos los precios de los pedidos que se a han realizado en el dia
    }

    return contador;
}
//////////////////////////////////////////////////////////////////////////////////

int contarPedidos(struct Pedido pedidos[], int cantPedidos, int modo) // cuenta los pedidos del dia
{

    int numeroPedidos = 0;
    for (int i = 0; i < cantPedidos; i++) // reccore for de i hasta cantPedidos
    {
        if ((pedidos[i].activo) == modo) // si el pedido esta activo = modo(si el pedido activo o no)
        {

            numeroPedidos++; // suma 1 a numeroPedidos
        }
    }
    return numeroPedidos;
}
//////////////////////////////////////////////////////////////////////////////////

int elMasPedido(struct Pedido pedidos[], int cantPedidos, int *indice)
{
    int max = 0;
    int arrplatos[100] = {0};             // arrplatos = a cantidad de veces que se pidio un plato
    for (int i = 0; i < cantPedidos; i++) // recorre de i hasta cantPedidos
    {
        arrplatos[pedidos[i].idPlato]++; // recorre la cantidad de veces que se pidio un plato
    }
    for (int j = 0; j < 100; j++) // recorre hasta 100
    {
        if (arrplatos[j] > max) // si arrplatos es mayor a al maximo
        {
            max = arrplatos[j]; // max pasa a valer lo que contiene arrplatos en la pocision j
            *indice = j;        // guarda en indice el id del plato mas pedido
        }
    }

    return max;
}
//////////////////////////////////////////////////////////////////////////////////
void clienteMayorGastoLogica(struct Pedido pedidos[], int cantPedidos, char clienteMax[100], float *gastoMax)
{
    // Arreglo auxiliar para acumular los gastos por cliente
    char clientes[100][100]; // guarda los nombres de los clientes donde cada fila es el id para el arreglo de gastos
    float gastos[100] = {0}; // acumulador de gastos de cada cliente
    int cantClientes = 0;    // guarda la cantdidad de clientes

    // Recorremos todos los pedidos
    for (int i = 0; i < cantPedidos; i++)
    { // primer for recorre los registros de pedido

        int encontrado = 0; // variable para verificar si el cliente esta o no en el arreglo
        // Buscamos si el cliente ya está registrado

        for (int j = 0; j < cantClientes; j++) // corrobora si el cliente esta o no en el arreglo
        {
            // segundo for recorre la matriz de clientes
            if (strcmp(pedidos[i].cliente, clientes[j]) == 0) // sirve para saber si el cliente ya esta en el arreglo a traves del strcmp
            {
                gastos[j] += pedidos[i].total; // en caso de que este dicho cliente se suman los pedidos realizados por el mismo
                encontrado = 1;                // se encontro el cliente, se pasa la variable a 1
                break;                         // sale del for
            }
        }

        // si lo encontramos, encontrados es = 1
        if (!encontrado) // si no se encontro el cliente en el arreglo (encontrado=0)

        {
            strcpy(clientes[cantClientes], pedidos[i].cliente); // se le agrega el cliente que no se encontro a la matriz
            gastos[cantClientes] = pedidos[i].total;            // se le suma el monto del pedido
            cantClientes++;                                     // se suma cantidad de clientes ya que se agrega uno nuevo
        }
    }
    // una vez hizo toda la vaina anterior
    // Buscar el cliente con mayor gasto
    int indiceMax = 0;

    for (int k = 1; k < cantClientes; k++) // permite recorrer todo el arrgelo buscando a ese cliente con mayor gasto
    {
        if (gastos[k] > gastos[indiceMax])
        {
            indiceMax = k; // se queda con el indice del cliente con mayor gasto
        }
    }
    // una vez recorre todo el arreglo
    strcpy(clienteMax, clientes[indiceMax]); // copia el nombre del cliente
    *gastoMax = gastos[indiceMax];           // guarda en el puntero el gasto maximo
}
// luego manda a la interfaz
