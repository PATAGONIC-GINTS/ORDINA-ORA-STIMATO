#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "..\Logica\Logica_Pedidos.h"
#include "..\Logica\Logica_Platos.h"
#include "..\Estructura\Estructuras.h"
//////////////////////////////////////////////////////////////////////////////////////////////////
void registrarPedidoLOGIC(struct Pedido pedidos[], int *cantPedidos, struct Plato platos[], int idPlato, int cantidad, char cliente[100])
{
    int aux=*cantPedidos;
    //asigna las variables desde la interfaz al registro(mete el dato en el registro :0)
    pedidos[*cantPedidos].id = aux;
    pedidos[*cantPedidos].idPlato = idPlato;
    pedidos[*cantPedidos].cantidad = cantidad;
    strcpy(pedidos[*cantPedidos].cliente, cliente);//copia la cadena de cliente en el arreglo de pedidos
    pedidos[*cantPedidos].total = cantidad * platos[idPlato].precio;
    pedidos[*cantPedidos].activo = 1;
    actualizarStock(&platos[idPlato], cantidad);
    (*cantPedidos)++; //incrementa la cantidad de pedidos por punteros
}
//////////////////////////////////////////////////////////////////////////////////////////////////
struct Pedido *listarPedidosActivosLogica(struct Pedido pedidos[], int cantPedidos, int *cantActivos)//funcion que retorna un puntero a registro
{

    int contador = 0;
    // Contar pedidos 
    if (cantPedidos <= 0){ //si la cantidad de pedidos es menor a 0 
        return NULL;//retorna vacio
    }    
    for (int i = 0; i < cantPedidos; i++)//for que recorre hasta cantidad de pediodos
    {
        if (pedidos[i].activo > 0)//si el activo del pedido es mayor a 1 
        {
            contador++;//se aumenta el contador 
        }
    }

    *cantActivos = contador;//cantActivos se iguala a contador

    if (contador == 0){ // si contador = a 0 
        return NULL;//retorna vacio
    }
    // Reservar memoria dinámica
    struct Pedido *activos = malloc(sizeof(struct Pedido) * (size_t)contador ); //reserva un espacio en memoria y multiploca el tamaño del struct pedido * el tamaño de contador 
    if (activos == NULL)//si activos esta vacio hace esto
    {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    // Copiar pedidos activos al nuevo array
    int j = 0;
    for (int i = 0; i < cantPedidos; i++)
    {
        if ((pedidos[i].activo) == 1)//si el activo = 1 
        {
            activos[j++] = pedidos[i];//se guarda en el arreglo de activos el pedido
        }
    }
    
    return activos;//retorna el pedido
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void pedidoCompletado(struct Pedido pedidos[], int idPedido)
{
    pedidos[idPedido].activo = 0; // realiza el cambio de 1 a 0 para marcar como completado el pedido
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int filtraPedidoClienteLogica(struct Pedido pedido, char cliente[])
{

    if (strcmp((pedido.cliente), cliente) == 0) //verifica si el nombre del cliente ingresado se encuentra en el arreglo de pedidos
      {

        return 1;//retorna 1 si asi lo es
    }
    else
    {

        return 0;//o sino
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void ordenarPorPrecio(struct Pedido pedidos[], int cantPedidos)
{
    // ordena el arreglo de pedidos a traves de un BUBBLE SORT
    bool inter = true;
    struct Pedido temporal;
    for (int i = 0; inter && i < cantPedidos - 1; i++)
    {
        inter = false;
        for (int j = 0; j < cantPedidos - i - 1; j++)
        {
            if ((pedidos[j].total) > (pedidos[j + 1].total))
            {
                temporal = pedidos[j];
                pedidos[j] = pedidos[j + 1];
                pedidos[j + 1] = temporal;
                inter = true;
            }
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int filtrarPedidoMontoLogica(struct Pedido pedidos, int monto)
{
    if (pedidos.total == monto) // si total del pedido es igual al monto del cliente
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void OrdenarPorId(struct Pedido pedidos[], int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;

        // Dividir en dos mitades
        OrdenarPorId(pedidos, inicio, medio);
        OrdenarPorId(pedidos, medio + 1, fin);

        // Combinar las mitades
        merge(pedidos, inicio, medio, fin);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int busquedaIdLogica(struct Pedido pedidos[], int cantPedidos, int valor)
{
    //busca en arreglo de pedidos a traves de id, se utiliza busqueda binaria
    int inicio = 0;
    int fin = cantPedidos - 1;

    while (inicio <= fin)
    {
       
        int medio = inicio + (fin - inicio) / 2;
       
        if (pedidos[medio].id == valor)
        {
            return medio; // Retorna el índice del valor
        }
        if (pedidos[medio].id < valor)
        {
            inicio = medio + 1;
        }
        else
        {
            fin = medio - 1;
        }
    }
return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void exportarPedidos(struct Pedido pedidos[], int cantPedidos)
{
    FILE *archivo; //puntero file que permite manejar el archiv
    archivo = fopen("..\\Archivos\\Pedidos.txt" , "w"); // abre el archivo 
    for (int i=0;i < cantPedidos;i++) // utilza for de i hasta cantPedidos
    {
        fprintf(archivo,"%i,%s,%f,%i,%i,%f,%i\n",pedidos[i].id,pedidos[i].cliente,pedidos[i].idPlato,pedidos[i].cantidad,pedidos[i].total,pedidos[i].activo);
    }
    fclose(archivo);
}
/////////////////////////////////////////////////////////////////////////
// Función que combina dos subarreglos en orden
void merge(struct Pedido pedidos[], int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    // Crear arreglos temporales
    struct Pedido izquierda[n1];
    struct Pedido derecha[n2];

    // Copiar los datos a los arreglos temporales
    for (int i = 0; i < n1; i++){ 
        izquierda[i] = pedidos[inicio + i];
        }
    for (int j = 0; j < n2; j++){ 
        derecha[j] = pedidos[medio + 1 + j];
}
    // Combinar los arreglos temporales de nuevo en arr[inicio..fin]
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if ((izquierda[i].id) <= (derecha[j].id)) {
            pedidos[k] = izquierda[i];
            i++;
        } else {
            pedidos[k] = derecha[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes
    while (i < n1) {
        pedidos[k] = izquierda[i];
        i++;
        k++;
    }
    while (j < n2) {
        pedidos[k] = derecha[j];
        j++;
        k++;
    }
}

