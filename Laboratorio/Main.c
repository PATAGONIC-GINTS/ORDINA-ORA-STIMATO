#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Interfaz\Interfaz_Platos.h"
#include "Interfaz\Interfaz_Pedidos.h"
#include "Interfaz\Interfaz_Platos.c"
#include "Interfaz\Interfaz_Pedidos.c"
#include "Estructura\Estructuras.h"
#include "Logica\Logica_Pedidos.h"
#include "Logica\Logica_Platos.h"
#include "Logica\Logica_Pedidos.c"
#include "Logica\Logica_Platos.c"
#include "Logica\estetica.c"
#include "Logica\estetica.h"
#include "Interfaz\Interfaz_Registro.h"
#include "Interfaz\Interfaz_Registro.c"
#include "Logica\Logica_Registro.h"
#include "Logica\Logica_Registro.c"
int main()
{
    int opcion;
    struct Plato platos[100];
    struct Pedido pedidos[100];
    int cantPlatos = 0, cantPedidos = 0;

    importarPlatos(platos, &cantPlatos);

    do
    {
        printf("++----------------------------------------++\n");
        printf("||         SISTEMA DE RESTAURANTE         ||\n");
        printf("++----------------------------------------++\n");
        printf("||                                        ||\n");
        printf("||    Estimado, seleccione una opcion:    ||\n");
        printf("||                                        ||\n");
        printf("||    [1] Mostrar menu                    ||\n");
        printf("||    [2] Mostrar reporte                 ||\n");
        printf("||    [3] Mostrar pedidos activos         ||\n");
        printf("||    [4] Buscar pedido por cliente       ||\n");
        printf("||    [5] Buscar pedido por monto         ||\n");
        printf("||    [6] Buscar pedido por ID            ||\n");
        printf("||    [7] Registrar pedido                ||\n");
        printf("||    [8] Registrar plato                 ||\n");
        printf("||    [9] Marcar pedido completado        ||\n");
        printf("||    [10] Exportar pedidos               ||\n");
        printf("||    [0] Salir del menu                  ||\n");
        printf("||                                        ||\n");
        printf("++----------------------------------------++\n");

        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            limpiarPantalla();
            mostrarCartaInterfaz(platos, cantPlatos);
            break;
        case 2:
            limpiarPantalla();
            registro(platos, pedidos, cantPedidos);
            break;
        case 3:
            limpiarPantalla();
            ListarPedidosActivosInterfaz(pedidos, cantPedidos);
            break;
        case 4:
            limpiarPantalla();
            filtraPedidoClienteInterfaz(pedidos, cantPedidos);
            break;
        case 5:
            limpiarPantalla();
            ordenarPorPrecio(pedidos, cantPedidos);
            filtrarPedidoMontoInterfaz(pedidos, cantPedidos);
            break;
        case 6:
            limpiarPantalla();
            OrdenarPorId(pedidos,0,cantPedidos);
            busquedaIdInterfaz(pedidos, cantPedidos);
            break;
        case 7:
            limpiarPantalla();
            registrarPedidoInterfaz(pedidos, &cantPedidos, platos, &cantPlatos);
            break;
        case 8:
            limpiarPantalla();
            registrarPlatoInterfaz(platos, &cantPlatos);
            break;
        case 9:
            limpiarPantalla();
            pedidoCompletadoInterfaz(pedidos);
            break;
        case 10:
            limpiarPantalla();
            exportarPedidos(pedidos, cantPedidos);
        case 0:
            break;
        default:
            printf("Opcion invalida. Por favor intente nuevamente.\n");
            break;
        }
    } while (opcion != 0);
    limpiarPantalla();
    exportarPlatos(platos, cantPlatos);
    printf("++--------------------------------------------------++\n");
    printf("||                                                  ||\n");
    printf("||  Gracias por utilizar el sistema de restaurante  ||\n");
    printf("||                Ordina Ora stimato                ||\n");
    printf("||                                                  ||\n");
    printf("++--------------------------------------------------++\n");
    return 0;
}