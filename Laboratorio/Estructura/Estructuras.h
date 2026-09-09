#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

struct Plato
{
    int id;           // Identificador único del plato
    char nombre[50]; // Nombre del plato
    float precio;     // Precio del plato
    int stock;        // Cantidad disponible
};

struct Pedido
{
    int id;            // Identificador único del pedido
    char cliente[100]; // Nombre del cliente
    int idPlato;       // ID del plato pedido
    int cantidad;      // Cantidad solicitada
    float total;       // Precio total del pedido
    int activo;        // 1 = activo, 0 = completado
};

#endif