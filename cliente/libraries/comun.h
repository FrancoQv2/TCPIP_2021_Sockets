#include <wchar.h>

void imprimir(const char* cadena);

/*
ñ: -92. El posta es 164 o \xa4
á: -96. El posta es 160 o \xa0
é: -126. El posta es 130 o \x82
í: -95. El posta es 161 o \xa1
ó: -94. El posta es 162 o \xa2
ú: -93. El posta es 163 o \xa3
ü: -127. El posta es 129 o \x81
Ñ: -91. El posta es 165 o \xa5
Á: -75. El posta es 181 o \xb5
É: -112. El posta es 144 o \x90
Í: -42. El posta es 214 o \xd6
Ó: -32. El posta es 224 o \xe0
Ú: -23. El posta es 233 o \xe9
Ü: -102. El posta es 154 o \x9a
¿: -88. El posta es 168 o \xa8
¡: -83. El posta es 173 o \xad
*/
wchar_t* conversionCaracterEspecial(const char car);
