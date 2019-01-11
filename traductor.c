#include "traductor.h"

int main()
{
    int cantidad = contarPalabras();
    if (cantidad > 0) // Se ejecuta solo si se pudo leer el archivo o se encontro al menos una palabra
    {
        nodo *arbol[cantidad];
        guardarPalabras(arbol, cantidad);
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

void guardarPalabras(nodo *arbol, int cantidad)
{
    FILE *archivo = fopen("traductor.in", "r");

    if (archivo)
    {
        int contador = 0;
        printf("\n");
        while (contador < cantidad)
        {
            char palabra[50];
            char word[50];
            fscanf(archivo, "%s %s\n", &palabra, &word);
            printf("%d) %s %s\n",contador + 1, palabra, word);

            nodo *nuevoNodo = malloc(sizeof(nodo));
            nuevoNodo->padre = NULL;
            nuevoNodo->hijoIzq = NULL;
            nuevoNodo->hijoDer = NULL;
            nuevoNodo->father = NULL;
            nuevoNodo->leftChild = NULL;
            nuevoNodo->rightChild = NULL;

            strcpy(nuevoNodo->espanol, palabra);
            strcpy(nuevoNodo->english, word);

            arbol[contador] = *nuevoNodo;   // Guardar el puntero al nodo en algun lado

            printf("Nodo ---> %s %s\n", nuevoNodo->espanol, nuevoNodo->english);
            
            contador++;
        }
        printf("\nass\n");
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
