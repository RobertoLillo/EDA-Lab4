#include "traductor.h"

int main()
{
    int cantidad = contarPalabras();
    if (cantidad > 0) // Se ejecuta solo si se pudo leer el archivo y se encontro al menos una palabra
    {
        // Se guardar las palabras del archivo en dos arreglos para las palabras en espanol e ingles
        string palabras[cantidad];
        string words[cantidad];
        guardarPalabras(palabras, words, cantidad);

        // El arbol se construye inicialmente con las palabras en espanol
        nodo *raiz = NULL;
        int i;
        for (i = 0; i < cantidad; i++)
        {
            nodo *nuevoNodo = (nodo *)malloc(sizeof(nodo));
            strcpy(nuevoNodo->espanol, palabras[i]);
            strcpy(nuevoNodo->english, words[i]);
            nuevoNodo->padre = NULL;
            nuevoNodo->hijoIzq = NULL;
            nuevoNodo->hijoDer = NULL;
            nuevoNodo->father = NULL;
            nuevoNodo->leftChild = NULL;
            nuevoNodo->rightChild = NULL;

            if (raiz == NULL)
            {
                raiz = nuevoNodo;
            }
            else
            {
                ingresarNodo(raiz, nuevoNodo);
            }
        }

        // Construccion del arbol en ingles por encima del arbol en espanol
        nodo *root = NULL;
        for (i = 0; i < cantidad; i++)
        {
            nodo *aux;
        } 
    }
    else // No se pudo leer el archivo
    {
        printf("Se encontro un problema, se cerrara el programa\n");
    }
}

int contarPalabras()
{
    FILE *archivo = fopen("traductor.in", "r");

    if (archivo)
    {
        int cantidad = 0;
        char linea[100];
        while (!feof(archivo))
        {
            fgets(linea, 100, archivo);
            cantidad++;
        }
        fclose(archivo);
        return cantidad;
    }
    else
    {
        printf("No se pudo leer el archivo\n");
        fclose(archivo);
        return -1;
    }
}

void guardarPalabras(string *palabras, string *words, int cantidad)
{
    FILE *archivo = fopen("traductor.in", "r");

    if (archivo)
    {
        int contador = 0;
        while (contador < cantidad)
        {
            fscanf(archivo, "%s %s\n", palabras[contador], words[contador]);
            contador++;
        }
        fclose(archivo);
        return;
    }
    else
    {
        printf("No se pudo leer el archivo\n");
        fclose(archivo);
        return;
    }
}

void ingresarNodo(nodo *raiz, nodo *nuevo)
{
    if (strcmp(nuevo->espanol, raiz->espanol) <= 0)
    {
        if (raiz->hijoIzq == NULL)
        {
            raiz->hijoIzq = nuevo;
            nuevo->padre = raiz;
        }
        else
        {
            ingresarNodo(raiz->hijoIzq, nuevo);
        }
    }
    else
    {
        if (raiz->hijoDer == NULL)
        {
            raiz->hijoDer = nuevo;
            nuevo->padre = raiz;
        }
        else{
            ingresarNodo(raiz->hijoDer, nuevo);
        }
    }
    return;
}

