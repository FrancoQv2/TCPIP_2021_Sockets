# tcp_ip_sockets
Aplicación utilizando sockets para TCP/IP

La carpeta .vscode contiene los archivos launch.json y tasks.json

En launch.json, en la etiqueta "program" se escribe la ruta donde estará el archivo ejecutable, incluyendo al ejecutable.
Con la variable predefinida ${workspaceFolder} se obtiene la dirección del directorio del entorno de trabajo. Así, escribiendo

    "program": "${workspaceFolder}\\main.exe"

el programa intentará ejecutar el archivo ejecutable "main.exe" que se encuentra en el entorno de trabajo.

En tasks.json, en la etiqueta "args" se escriben los argumentos del comando gcc. En nuestro caso, y para la organización del entorno, vamos a:

 1) Crear el archivo ejecutable en el directorio principal del entorno de trabajo;
 2) compilar el archivo principal .c que se encuentra en src/;
 3) compilar los archivos .c que haya en src/implementations para que se implementen los archivos de cabecera;
 4) agregar opciones para trabajar con sockets;
 5) agregado de una opción para explicitar el directorio de archivos de cabecera.

Estos argumentos quedarían como sigue...

    "args": [
        "-g",
        "-o",
        "${workspaceFolder}\\main.exe",
        "${workspaceFolder}\\src\\main.c",
        "${workspaceFolder}\\src\\implementations\\*.c",
        "-lws2_32",
        "-lwsock32",
        "-L",
        "$MinGW\\lib",
        "-I",
        "${workspaceFolder}\\libraries"
    ]

De esta forma, la estructura quedaría como sigue en el directorio principal de trabajo (ya sea el del servidor o el del cliente):

EntornoTrabajo \
 ┣ .vscode \
 ┃ ┣ launch.json \
 ┃ ┗ tasks.json \
 ┣ libraries \
 ┣ src \
 ┃ ┣ implementations \
 ┃ ┗ main.c \
 ┗ main.exe 
 
 
     while (1) {
        printf("[SERVER]: ");
        
        do {
            bzero(buffer, BUFFER_MAX);
            fgets(buffer, BUFFER_MAX, stdin);
                if((int)strlen(buffer)+1 > 199) flag_ok = 0;
        } while ((int)strlen(buffer)+1 > 199 );
        
        if(flag_ok){
            n = sendto(socketfd, buffer, BUFFER_MAX, 0, (struct sockaddr *)&client, sizeof(struct sockaddr_in));    
        }
        else{
            printf("Tamanio de la trama excedido");
            while(getchar() != '\n');
            flag_ok = 1;
        }
        if (n < 0) {
            printf("sendto()");
        }
        
    }
}
