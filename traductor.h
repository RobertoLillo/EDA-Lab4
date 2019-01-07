#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/********** Estructuras **********/
typedef struct Nodo {
    char *espanol;
    struct Nodo *padre;
    struct Nodo *hijoIzq;
    struct Nodo *hijoDer;
    char *english;
    struct Nodo *father;
    struct Nodo *leftChild;
    struct Nodo *RightChild;
} nodo;

/********** Prototipos **********/
int contarPalabras();

