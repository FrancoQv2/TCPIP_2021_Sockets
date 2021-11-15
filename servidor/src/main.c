#include <stdio.h>
#include <locale.h>

int main()
{
    // Permite caracteres especiales en los prints si se imprime como en la línea 9
    setlocale(LC_ALL, "");

    printf("%ls", L"¡Hola mundo!");

    fgetc(stdin);

    return 0;
}