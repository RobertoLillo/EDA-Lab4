#include "traductor.h"

int main()
{
    int cantidad = contarPalabras();
    if (cantidad > 0) // Se ejecuta solo si se pudo leer el archivo o se encontro al menos una palabra
    {
        
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