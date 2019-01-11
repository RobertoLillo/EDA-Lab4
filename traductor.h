#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/********** Estructuras **********/
typedef struct Nodo
{
    char espanol[50];
    struct Nodo *padre;
    struct Nodo *hijoIzq;
    struct Nodo *hijoDer;
    char english[50];
    struct Nodo *father;
    struct Nodo *leftChild;
    struct Nodo *rightChild;
} nodo;

/********** Prototipos **********/
int contarPalabras();
void guardarPalabras(nodo *arbol, int cantidad);
