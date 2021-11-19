# Aplicación utilizando sockets para TCP/IP

## Integrantes

- Boeri, Benjamín
- Israilev, Mateo
- Murcani, Julián David
- Quevedo, Franco

## Descripción

Esta aplicación permite enviar mediante una aplicación de sockets y utilizando el protocolo UDP, mensajes de broadcast a la red local desde un host Servidor a todos los host Clientes que se encuentren ejecutando la apliación Cliente.

La aplicación de sockets Servidora utilizará un puerto aleatorio entre 50.000 y 51.000, y cada aplicación Cliente utiliza el puerto 2500 de su host.

## Compilación

Desde la consola pararse en el directorio del repositorio y ejecutar el comando:

    make <target>

Donde *target* puede ser alguna de las siguientes opciones:

- *server:*     compila la aplicación Servidora para Windows

- *client:*     compila la aplicación Cliente para Windows

- *server_linux:* compila la aplicación Servidora para Linux

- *client_linux:* compila la aplicación Cliente para Linux


## Ejecución

Para levantar el Servidor de Windows en necesario pasar por argumento al momento de ejecutarlo la IP de broadcast de la red local. Por ejemplo:

    > server.exe 192.168.100.255

Las demás aplicaciones no necesitan argumentos extras para su ejecución.


## Debug

La carpeta .vscode contiene los archivos *launch.json* y *tasks.json*

En *launch.json*, en la etiqueta "program" se escribe la ruta donde estará el archivo ejecutable, incluyendo al ejecutable.
Con la variable predefinida ${workspaceFolder} se obtiene la dirección del directorio del entorno de trabajo. Así, escribiendo

    "program": "${workspaceFolder}\\server.exe"

el programa intentará ejecutar el archivo ejecutable "server.exe" que se encuentra en el entorno de trabajo.

En *tasks.json*, en la etiqueta "args" se escriben los argumentos del comando gcc, lo cuales quedarían como sigue...

    "args": [
        "-fdiagnostics-color=always",
        "-g",
        "-o",
        "${workspaceFolder}\\server.exe",
        "${workspaceFolder}\\app_client\\src\\server.c",
        "-lws2_32",
        "-lwsock32",
        "-L",
        "$MinGW\\lib"
    ]

## Estructura del proyecto

La estructura final del proyecto es:

    Entorno de Trabajo \
        ┣ .vscode \
            ┃ ┣ launch.json \
              ┗ tasks.json \
        ┣ app_client \
            ┣ src \
              ┗ client.c \
        ┣ app_server \
            ┣ src \
              ┗ server.c \
        ┣ docs \
        ┣ examples \
        ┗ server.exe 
