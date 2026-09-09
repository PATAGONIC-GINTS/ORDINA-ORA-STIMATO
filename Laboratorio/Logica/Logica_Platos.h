#ifndef LOGICA_PLATOS_H
#define LOGICA_PLATOS_H

#include "..\Estructura\Estructuras.h"
void convertirminus(char aux[]);
int comprobacionNum(float precio);
int verificarPlato(struct Plato platos[], int cantPlatos, char nombre[100]);
int verificarStock(struct Plato platos[],int op, int cantidadsolicita,int cantidad);
void actualizarStock(struct Plato *plato, int cantidadVendida);
void registrarPlatoLogica(struct Plato *platos,char nombre[100],float precio,int stock,int id);
struct Plato* MostrarCartaLogica(struct Plato platos[], int cantPlatos, int *cont);
void importarPlatos(struct Plato platos[], int *cantPlatos);
void exportarPlatos(struct Plato platos[], int cantPlatos);
#endif