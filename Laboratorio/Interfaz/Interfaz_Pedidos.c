#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "..\Interfaz\Interfaz_Platos.h"
#include "..\Interfaz\Interfaz_Pedidos.h"
#include "..\Logica\Logica_Platos.h"
#include "..\Logica\Logica_Pedidos.h"
#include "..\Estructura\Estructuras.h"
//////////////////////////////////////////////////////////////////////////////////////////////////
void registrarPedidoInterfaz(struct Pedido pedidos[], int *cantPedidos, struct Plato platos[], int *cantPlatos)
{
    int opcionid, opcionstock, aux = 0;
    char cliente[100];
    printf("++----------------------------------------++\n");
    printf("Ingrese el nombre del cliente: "); // se le pide que ingrese el nombre
    getchar();                                 // espera que el usuario ingrese un carácter. Una vez que se presiona una tecla, el carácter se lee y se devuelve.
    fgets(cliente, sizeof(cliente), stdin);    // Lee el nombre de cliente con espacios incluidos
    cliente[strcspn(cliente, "\n")] = 0;    // quita el salto de linea del fgets    
    convertirminus(cliente);                   // convierte en minuscula para tener siempre un mismo formato y no tener problemas al comparar

    do
    {
        mostrarCartaInterfaz(platos, *cantPlatos); // llama a la funcion mostrarCartaInterfaz
        printf("ID del plato: \n");
        scanf("%d", &opcionid);
        printf("Cantidad: \n");
        scanf("%d", &opcionstock);

        if (verificarStock(platos, opcionid, opcionstock, *cantPlatos)) // llama a la funcion verificarStock y devuelve "1" si no hay stock y "0" si hay stock del plato
        {
            printf("Los datos ingresados son incorrectos\n");
            aux = 1; // si se cumple aux es = 1
        }
        else
        {
            aux = 0; // sino aux = 0
        }
    } while (aux != 0); // el bucle continua si aux es diferente de 0

    // Llamamos a la función lógica
    registrarPedidoLOGIC(pedidos, cantPedidos, platos, opcionid, opcionstock, cliente);

    printf("Total del pedido: $%.2f\n", pedidos[*cantPedidos - 1].total);
    printf("++----------------------------------------++\n");
    //*cantPedidos = (*cantPedidos + 1);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void ListarPedidosActivosInterfaz(struct Pedido pedidos[], int cantPedidos)
{
    int cont = 0;
    struct Pedido *activos = listarPedidosActivosLogica(pedidos, cantPedidos, &cont); // se reserva un espacio de memoria para la funcion listarPedidosActivosLogica
    printf("++----------------------------------------++\n");
    for (int i = 0; i < cont; i++) // for que rcorre hasta la cantidad de
    {
        printf("||Pedido %d || Cliente: %s || Plato ID: %d || Cant: %d || Total: %.2f||\n", activos[i].id, activos[i].cliente, activos[i].idPlato, activos[i].cantidad, activos[i].total);
    }
    printf("++----------------------------------------++\n");
    free(activos); // libera memoria
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void noEstaCliente() // a la hora de llamarla devuelve el printf.

{
    printf("El cliente no realizo ningun pedido :(\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void filtraPedidoClienteInterfaz(struct Pedido pedidos[], int cantPedidos)
{
    int aux = 0;
    char cliente[100];
    printf("++----------------------------------------++\n");
    printf("Ingrese el nombre del cliente que desea buscar\n");
    scanf("%s",cliente);
    convertirminus(cliente);              // convierte el nombre del cliento a minuscula para no tener problemas a la hora de comparar
    for (int i = 0; i < cantPedidos; i++) // for que recorre hasta la cantidad de pedidos
    {
        if (filtraPedidoClienteLogica(pedidos[i], cliente)) // llama a la funcion filtraPedidoClienteLogica y verifica el pedido del cliente solicitado en la linea "69"
        {
            // imprime el pedido
            printf("El pedido es el siguiente:\n");
            printf("ID del pedido: %i\n", pedidos[i].id);
            printf("El nombre del cliente es: %s\n", pedidos[i].cliente);
            printf("ID del plato: %i\n", pedidos[i].idPlato);
            printf("Cantidad del plato: %i\n", pedidos[i].cantidad);
            printf("El precio total del pedido  es: %.2f\n", pedidos[i].total);
            if (pedidos[i].activo == 1) // verifica si el pedido se entrego o no
            {
                printf("El pedido todavia no fue entregado\n");
            }
            else
            {
                printf("El pedido ya fue entregado\n");
            }
            aux = 1;
        }
    }
    if (!aux) // si aux = 0 significa que el cliente no se encuentra, debido a que nunca entro al if anterior
    {
        noEstaCliente(); // llamado de funcion
    }
    printf("++----------------------------------------++\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void filtrarPedidoMontoInterfaz(struct Pedido pedidos[], int cantPlatos)
{
    float monto;
    int aux = 0;        
    printf("++----------------------------------------++\n");
    printf("Ingrese el monto que desea buscar\n");
    scanf("%f", &monto);
    for (int i = 0; i < cantPlatos; i++) // for que recorre hasta cantidad de platos
    {
        if (filtrarPedidoMontoLogica(pedidos[i], monto)) // filtra los pedidos a travez del monto solicitad en la linea 106. llama a la funcion filtrarPedidoMontoLogica
        {
            // imprime el pedido requerido
            printf("El pedido es el siguiente:\n");
            printf("ID del pedido: %i\n", pedidos[i].id);
            printf("El nombre del cliente es: %s\n", pedidos[i].cliente);
            printf("ID del plato: %i\n", pedidos[i].idPlato);
            printf("Cantidad del plato: %i\n", pedidos[i].cantidad);
            printf("El precio total del pedido  es: %.2f\n", pedidos[i].total);
            if (pedidos[i].activo == 1) // verifica si el pedido se entrego o no
            {
                printf("El pedido todavia no fue entregado\n");
            }
            else
            {
                printf("El pedido ya fue entregado\n");
            }
            aux = 1;
        }
    }
    if (!aux) // si aux = 0 significa que no se encontro al cliente por el monto
    {
        noHayMonto();
    }
    printf("++----------------------------------------++\n");   
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void noHayMonto() // imprime que no se han encontrado el pedido requerido
{
    printf("No se han encontrado pedidos\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////

void busquedaIdInterfaz(struct Pedido pedidos[], int cantPedidos)
{
    printf("++----------------------------------------++\n");
    int valor, aux;
    printf("Ingrese el id del pedido que desea buscar:\n");
    scanf("%i", &valor);
    aux = busquedaIdLogica(pedidos, cantPedidos, valor); // guarda en un auxiliar la funcion busquedaIdLogica
    if (aux != -1)                                       // ya que en la logica si retorna -1 no se encontro el valor
    {
        // imprime el pedido
        printf("El pedido es el siguiente:\n");
        printf("ID del pedido: %i\n", pedidos[aux].id);
        printf("El nombre del cliente es: %s\n", pedidos[aux].cliente);
        printf("ID del plato: %i\n", pedidos[aux].idPlato);
        printf("Cantidad del plato: %i\n", pedidos[aux].cantidad);
        printf("El precio total del pedido  es: %.2f\n", pedidos[aux].total);
        if (pedidos[aux].activo == 1) // verifica si el pedido se entrego
        {
            printf("El pedido todavia no fue entregado\n");
        }
        else
        {
            printf("El pedido ya fue entregado\n");
        }
    }
    else
    {
        printf("No se ha encontrado el pedido\n");
    }
    printf("++----------------------------------------++\n");
}

void pedidoCompletadoInterfaz(struct Pedido pedidos[]) //
{
    int id;
    printf("++----------------------------------------++\n");
    printf("ingrese el id del pedido completado\n");
    scanf("%i", &id);
    pedidoCompletado(pedidos, id); // llama a la funcion logica |
    printf("++----------------------------------------++\n");
}