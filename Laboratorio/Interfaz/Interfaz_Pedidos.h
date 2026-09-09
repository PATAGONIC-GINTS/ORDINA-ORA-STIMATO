#ifndef INTERFAZ_PEDIDOS_H
#define INTERFAZ_PEDIDOS_H

#include "..\Logica\Logica_Pedidos.h"
#include "..\Estructura\Estructuras.h"

void registrarPedidoInterfaz(struct Pedido pedidos[], int *cantPedidos, struct Plato platos[], int *cantPlatos);
void ListarPedidosActivosInterfaz(struct Pedido pedidos[], int cantPedidos);
void filtrarPedidoMontoInterfaz(struct Pedido pedidos[], int cantPlatos);
void noEstaCliente();
void noHayMonto();
void busquedaIdInterfaz(struct Pedido pedidos[],int cantPedidos);
void filtraPedidoClienteInterfaz(struct Pedido pedidos[], int cantPedidos);
void pedidoCompletadoInterfaz (struct Pedido pedidos[]);
#endif
