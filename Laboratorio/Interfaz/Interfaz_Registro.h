#ifndef INTERFAZ_REGISTRO_H
#define INTERFAZ_REGISTRO_H

#include "..\Estructura\Estructuras.h"
#include "..\Logica\Logica_Registro.h"

void registro(struct Plato platos[], struct Pedido pedidos[], int cantPedidos);
void clienteMayorGastoInterfaz(struct Pedido pedidos[], int cantPedidos);

#endif