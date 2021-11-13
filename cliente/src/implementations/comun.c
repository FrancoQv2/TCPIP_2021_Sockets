#include "comun.h"
#include <stdio.h>

void imprimir(const char* cadena)
{
    char esCaracterEspecial = 0;
    for(char* p = (char*)cadena; *p != '\0'; p++)
    {
        if(*p == -61 || *p == -62)
            esCaracterEspecial = *p;
        else if(esCaracterEspecial)
        {
            printf("%c", conversionCaracterEspecial(esCaracterEspecial, *p));
            esCaracterEspecial = 0;
        }
        else
            printf("%c", *p);
    }
}

unsigned char conversionCaracterEspecial(const char acceso, const char car)
{
    if(acceso == -61)
    {
        switch(car)
        {
            case -79:
                return 164;
            case -95:
                return 160;
            case -87:
                return 130;
            case -83:
                return 161;
            case -77:
                return 162;
            case -70:
                return 163;
            case -68:
                return 129;
            case -111:
                return 165;
            case -127:
                return 181;
            case -119:
                return 144;
            case -115:
                return 214;
            case -109:
                return 224;
            case -102:
                return 233;
            case -100:
                return 154;
            default:
                return 0;
        }
    }

    if(acceso == -62)
    {
        switch(car)
        {
            case -65:
                return 168;
            case -95:
                return 173;
            default:
                return 0;
        }
    }
}