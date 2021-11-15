#include "comun.h"
#include <stdio.h>
#include <locale.h>

void imprimir(const char* cadena)
{
    setlocale(LC_ALL, "");
    for(char* p = (char*)cadena; *p != '\0'; p++)
    {

        if(*p < 0)
            wprintf(L"%ls", conversionCaracterEspecial(*p));
        else
            printf("%c", *p);
    }
}

wchar_t* conversionCaracterEspecial(const char car)
{
    switch(car)
    {
        case -92:
            return L"ñ"; // devuelve 'ñ'
        case -96:
            return L"á"; // devuelve 'á'
        case -126:
            return L"é"; // devuelve 'é'
        case -95:
            return L"í"; // devuelve 'í'
        case -94:
            return L"ó"; // devuelve 'ó'
        case -93:
            return L"ú"; // devuelve 'ú'
        case -127:
            return L"ü"; // devuelve 'ü'
        case -91:
            return L"Ñ"; // devuelve 'Ñ'
        case -75:
            return L"Á"; // devuelve 'Á'
        case -112:
            return L"É"; // devuelve 'É'
        case -42:
            return L"Í"; // devuelve 'Í'
        case -32:
            return L"Ó"; // devuelve 'Ó'
        case -23:
            return L"Ú"; // devuelve 'Ú'
        case -102:
            return L"Ü"; // devuelve 'Ü'
        case -88:
            return L"¿"; // devuelve '¿'
        case -83:
            return L"¡"; // devuelve '¡'
        default:
            return 0;
    }
}