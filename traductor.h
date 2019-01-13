#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/********** Tipos de datos y estructuras **********/
typedef char string[51];

typedef struct Nodo
{
    string espanol;
    struct Nodo *padre;
    struct Nodo *hijoIzq;
    struct Nodo *hijoDer;
    string english;
    struct Nodo *father;
    struct Nodo *leftChild;
    struct Nodo *rightChild;
} nodo;

/********** Prototipos **********/
int contarPalabras();
void guardarPalabras(string *palabras, string *words, int cantidad);
void ingresarNodo(nodo *raiz, nodo *nuevo);
void insertNode(nodo *raiz, nodo *root, string palabra, string word);
void pointNode(nodo *root, int direccion, nodo *raiz, string palabra);
void traducir(nodo *raiz, string palabra, int opcion);
void imprimir(nodo *raiz);