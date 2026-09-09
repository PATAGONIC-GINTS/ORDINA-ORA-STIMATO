#ifndef LOGICA_PEDIDOS_H
#define LOGICA_PEDIDOS_H

#include "..\Estructura\Estructuras.h"

void registrarPedidoLOGIC (struct Pedido pedidos[], int *cantPedidos, struct Plato platos[], int idPlato, int cantidad, char cliente[100]);
void pedidoCompletado (struct Pedido pedidos[], int idPedido);
struct Pedido* listarPedidosActivosLogica (struct Pedido pedidos[], int cantPedidos, int *cantActivos);
int filtraPedidoClienteLogica (struct Pedido pedido, char cliente[]);
int filtrarPedidoMontoLogica (struct Pedido pedidos, int monto);
void ordenarPorPrecio (struct Pedido pedidos[],int cantPedidos);
void OrdenarPorId(struct Pedido pedidos[], int inicio, int fin);
int busquedaIdLogica(struct Pedido pedidos[], int tamaño, int valor);
void exportarPedidos(struct Pedido pedidos[], int cantPedidos);
void merge(struct Pedido pedidos[], int inicio, int medio, int fin);

#endif