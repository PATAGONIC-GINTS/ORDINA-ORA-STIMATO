#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "..\Logica\estetica.h"
#include "..\Estructura\Estructuras.h"

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[H");
    fflush(stdout);
#endif
}

