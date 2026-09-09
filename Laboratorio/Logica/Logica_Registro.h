#ifndef LOGICA_REGISTRO_H
#define LOGICA_REGISTRO_H

#include "..\Estructura\Estructuras.h"

float platita(struct Pedido pedidos[], int cantpedidos);
int contarPedidos(struct  Pedido pedidos[],int cantPedidos,int modo);
int elMasPedido(struct Pedido pedidos[], int cantPedidos, int *indice);
void clienteMayorGastoLogica(struct Pedido pedidos[], int cantPedidos, char clienteMax[100], float *gastoMax);
#endif