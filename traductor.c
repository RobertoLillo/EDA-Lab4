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

        // Construccion del arbol en ingles por encima del arbol en espanol, la raiz es la misma
        for (i = 1; i < cantidad; i++)
        {
            insertNode(raiz, raiz, palabras[i], words[i]);
        }

        // Interaccion con el usuario por consola
        printf("\nTraductor Little C's\n");
        int opcion, verificador;
        int flag = 0;
        while (flag == 0)
        {
            printf("\nIngrese una de las siguientes opciones:\n");
            printf("\t1) Traduccion espanol a ingles.\n");
            printf("\t2) Traduccion ingles a espanol.\n");
            printf("\t3) Salir.\n");
            printf("Opcion -> ");

            verificador = scanf("%d", &opcion);
            if (verificador == EOF)
            {
                printf("\nError.\n");
            }
            else if (verificador == 0)
            {
                printf("\nSe encontro un problema, se cerrara el programa.\n");
                break;
            }
            else
            {
                if (opcion == 1)
                {
                    string palabraEsp;
                    printf("\nIngrese la palabra a traducir: ");
                    scanf("%s", palabraEsp);
                    traducir(raiz, palabraEsp, 1);
                }
                else if (opcion == 2)
                {
                    string palabraEng;
                    printf("\nIngrese la palabra a traducir: ");
                    scanf("%s", palabraEng);
                    traducir(raiz, palabraEng, 2);
                }
                else
                {
                    printf("\nAdios!\n\n");
                    flag = 1;
                }
            }
        }
    }
    else // No se pudo leer el archivo
    {
        printf("Se encontro un problema, se cerrara el programa\n");
    }
}

// Se cuentan las palabras para crear un arreglo estatico donde guardarlas.
//
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

// Se guardan las palabras en los arreglos estaticos anteriormente mencionados en contarPalabras.
// palabras: arreglo para las palabras en espanol.
// words: arreglo para las palabras en ingles.
// cantidad: cantidad de lineas por leer.
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

// Se colocan los nodos para armar el arbol en espanol inicialmente.
// raiz: puntero al nodo raiz de un arbol.
// nuevo: puntero al nuevo nodo que se quiere ingresar al arbol.
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
        else
        {
            ingresarNodo(raiz->hijoDer, nuevo);
        }
    }
    return;
}

// Busca el lugar y direccion donde colocar el pseudonodo para ingles
// raiz: puntero para el espanol
// root: puntero para el ingles
// palabra: palabra en espanol
// word: palabra en ingles
void insertNode(nodo *raiz, nodo *root, string palabra, string word)
{
    if (strcmp(word, root->english) <= 0)
    {
        if (root->leftChild == NULL)
        {
            pointNode(root, 0, raiz, palabra);
        }
        else
        {
            insertNode(raiz, root->leftChild, palabra, word);
        }
    }
    else
    {
        if (root->rightChild == NULL)
        {
            pointNode(root, 1, raiz, palabra);
        }
        else
        {
            insertNode(raiz, root->rightChild, palabra, word);
        }
    }
    return;
}

// Busca y direcciona el puntero hacia el nodo correspondiente
// root: puntero al nodo en ingles
// direccion: 0 izquierda - 1 derecha
// raiz: puntero para las palabras en espanol
// palabra: palabra en espanol
void pointNode(nodo *root, int direccion, nodo *raiz, string palabra)
{
    if (strcmp(palabra, raiz->espanol) == 0)
    {
        if (direccion == 0)
        {
            root->leftChild = raiz;
            raiz->father = root;
        }
        else
        {
            root->rightChild = raiz;
            raiz->father = root;
        }
        return;
    }
    else
    {
        if (strcmp(palabra, raiz->espanol) <= 0)
        {
            pointNode(root, direccion, raiz->hijoIzq, palabra);
        }
        else
        {
            pointNode(root, direccion, raiz->hijoDer, palabra);
        }
    }
}

// Buscar la palabra que se quiere traducir en el arbol.
// raiz: puntero al nodo raiz del arbol.
// palabra: palabra que se quiere traducir.
// opcion: 1 para traducir al ingles, 2 para traducir al espanol.
void traducir(nodo *raiz, string palabra, int opcion)
{
    if (opcion == 1)
    {
        // Busqueda de la palabra
        if (strcmp(palabra, raiz->espanol) == 0)
        {
            // Traduccion de la palabra
            printf("\nLa palabra traducida al ingles es: %s\n\n", raiz->english);
            imprimir(raiz);
            return;
        }
        else
        {
            if (strcmp(palabra, raiz->espanol) <= 0)
            {
                traducir(raiz->hijoIzq, palabra, opcion);
            }
            else
            {
                traducir(raiz->hijoDer, palabra, opcion);
            }
        }
    }
    else
    {
        // Busqueda de la palabra
        if (strcmp(palabra, raiz->english) == 0)
        {
            // Traduccion de la palabra
            printf("\nLa palabra traducida al espanol es: %s\n\n", raiz->espanol);
            imprimir(raiz);
            return;
        }
        else
        {
            if (strcmp(palabra, raiz->english) <= 0)
            {
                traducir(raiz->leftChild, palabra, opcion);
            }
            else
            {
                traducir(raiz->rightChild, palabra, opcion);
            }
        }
    }
}

// Se muestran por pantalla todos los datos relacionados al nodo donde se encuentra la palabra traducida.
// nodoPalabra: puntero al nodo donde esta la palabra traducida.
void imprimir(nodo *nodoPalabra)
{
    // Mostrar padre espanol
    if (nodoPalabra->padre == NULL)
    {
        printf("El nodo no tiene padre en el idioma espanol.\n");
    }
    else
    {
        printf("El nodo padre del idioma espanol es: %s/%s\n", nodoPalabra->padre->espanol, nodoPalabra->padre->english);
    }

    // Mostrar hijo izquierdo espanol
    if (nodoPalabra->hijoIzq == NULL)
    {
        printf("El nodo no tiene hijo izquierdo en el idioma espanol.\n");
    }
    else
    {
        printf("El nodo hijo izquierdo del idioma espanol es: %s/%s\n", nodoPalabra->hijoIzq->espanol, nodoPalabra->hijoIzq->english);
    }

    // Mostrar hijo derecho espanol
    if (nodoPalabra->hijoDer == NULL)
    {
        printf("El nodo no tiene hijo derecho en el idioma espanol.\n");
    }
    else
    {
        printf("El nodo hijo derecho del idioma espanol es: %s/%s\n", nodoPalabra->hijoDer->espanol, nodoPalabra->hijoDer->english);
    }

    // Mostrar padre ingles
    if (nodoPalabra->father == NULL)
    {
        printf("El nodo no tiene padre en el idioma ingles.\n");
    }
    else
    {
        printf("El nodo padre del idioma ingles es: %s/%s\n", nodoPalabra->father->espanol, nodoPalabra->father->english);
    }

    // Mostrar hijo izquierdo ingles
    if (nodoPalabra->leftChild == NULL)
    {
        printf("El nodo no tiene hijo izquierdo en el idioma ingles.\n");
    }
    else
    {
        printf("El nodo hijo izquierdo del idioma ingles es: %s/%s\n", nodoPalabra->leftChild->espanol, nodoPalabra->leftChild->english);
    }

    // Mostrar hijo derecho ingles
    if (nodoPalabra->rightChild == NULL)
    {
        printf("El nodo no tiene hijo derecho en el idioma ingles.\n");
    }
    else
    {
        printf("El nodo hijo derecho del idioma ingles es: %s/%s\n", nodoPalabra->rightChild->espanol, nodoPalabra->rightChild->english);
    }
    return;
}