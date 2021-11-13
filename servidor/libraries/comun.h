void imprimir(const char* cadena);

/*
A los siguientes caracteres se accede con el número -61.
ñ: -79. El posta es 164 o \xa4
á: -95. El posta es 160 o \xa0
é: -87. El posta es 130 o \x82
í: -83. El posta es 161 o \xa1
ó: -77. El posta es 162 o \xa2
ú: -70. El posta es 163 o \xa3
ü: -68. El posta es 129 o \x81
Ñ: -111. El posta es 165 o \xa5
Á: -127. El posta es 181 o \xb5
É: -119. El posta es 144 o \x90
Í: -115. El posta es 214 o \xd6
Ó: -109. El posta es 224 o \xe0
Ú: -102. El posta es 233 o \xe9
Ü: -100. El posta es 154 o \x9a

A estos dos últimos se accede primero con el número -62.
¿: -65. El posta es 168 o \xa8
¡: -95. El posta es 173 o \xad
*/
unsigned char conversionCaracterEspecial(const char acceso, const char car);
