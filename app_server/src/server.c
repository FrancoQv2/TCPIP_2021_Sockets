#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h>

// #define LOCAL_BROADCAST "192.168.1.255"
#define CLIENTS_PORT 2500
#define BUFFER_MAX 200

// Se agrega la librería ws2_32 a lista de dependencias
#pragma comment(lib, "ws2_32.lib")

unsigned char ip_valida(const char* ip);
void charizard();

int main(int argc, const char* argv[]) {
    system("cls");
    charizard();

    // Para trabajar con caracteres hispanos
    setlocale(LC_ALL, "");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    if (argc != 2) {
        fprintf(stderr, "%ls", L"Agregar la IP de broadcast de su red local (server_win.exe <ip_broadcast>)");
        return -1;
    }

    if (!ip_valida(argv[1])) {
        fprintf(stderr, "%ls", L"Debe ser una IPv4 válida.");
        return -1;
    }

    const char* LOCAL_BROADCAST = argv[1];

    srand(time(NULL));

    WSADATA wsa;
    SOCKET socketfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int SERVER_PORT = 50000 + rand() % 101;  // N° aleatorio entre 50.000 y 50.100

    char* buf_tx = malloc(512);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "%ls %d", "Falló. Código de error:", WSAGetLastError());
        exit(-1);
    }

    // Creo el socket
    if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR) {
        fprintf(stderr, "%ls %d", L"Falló la creación del socket", WSAGetLastError());
        exit(-1);
    }

    // Configuro los parametros del server
    server.sin_family = AF_INET;           // Family IPv4
    server.sin_port = htons(SERVER_PORT);  // Puerto del servidor
    server.sin_addr.s_addr = INADDR_ANY;   // IP 0.0.0.0

    // Asocio la IP y puerto del server al socket
    if (bind(socketfd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        fprintf(stderr, "%ls %d", L"Falló el bind con código de error:", WSAGetLastError());
        exit(-1);
    }

    // Configuro los parametros de los clientes
    client.sin_family = AF_INET;                          // Family IPv4
    client.sin_port = htons(CLIENTS_PORT);                // Puerto de los hosts clientes
    client.sin_addr.s_addr = inet_addr(LOCAL_BROADCAST);  // IP broadcast de la red local

    // Configuro las opciones del socket para que acepte broadcast
    int broad = 1;
    if (setsockopt(socketfd, SOL_SOCKET, SO_BROADCAST, (void*)&broad, sizeof(broad)) < 0) {
        fprintf(stderr, "%ls", L"Error en la habilitación del broadcast.");
        exit(-1);
    }

    printf("=========================================================================\n");
    printf("%ls", L"Bienvenido!\nEsta es la aplicación Servidor\n\n");
    printf("Autores: Boeri, Israilev, Murcani, Quevedo\n\n");
    printf("=========================================================================\n\n");

    int index;
    /* Aceptar la información de los sockets entrantes en forma iterativa */
    while (1) {
        size_t teclas_apretadas;
        do {
            teclas_apretadas = 0;
            printf("[SERVER]: ");

            fflush(stdin);
            memset(buf_tx, 0, BUFFER_MAX + 2);

            int tecla = 0;
            index = 0;
            while (tecla != 13)  // El bucle se repetirá mientras la tecla apretada no sea el enter
            {
                if (_kbhit()) {
                    tecla = _getch();

                    // Para omitir las teclas Fn
                    if (_kbhit()) {
                        tecla = _getch();
                        continue;
                    }

                    if (tecla != 13) {
                        // La tecla 8 es el retroceso
                        if (tecla != 8) {
                            if (teclas_apretadas < BUFFER_MAX) {
                                fputc(tecla, stdout);
                                teclas_apretadas++;
                                buf_tx[index++] = tecla;
                            }
                        } else if (teclas_apretadas > 0)  // Que solo se permita retroceder si ya se escribió algo
                        {
                            teclas_apretadas--;
                            if (teclas_apretadas < BUFFER_MAX)
                                buf_tx[--index] = 0;
                            printf("\b \b");
                        }
                    }
                }
            }
            fputc('\n', stdout);

        } while (teclas_apretadas > BUFFER_MAX);

        buf_tx[index++] = '\n';
        buf_tx[index++] = '\0';

        // Envia el mensaje escrito a todos los host de la red
        if (sendto(socketfd, buf_tx, index, 0, (struct sockaddr*)&client, sizeof(struct sockaddr_in)) < 0) {
            fprintf(stderr, "No se pudo enviar mensaje");
            exit(-1);
        }
        if (strcmp(buf_tx, "exit\n") == 0) {
            closesocket(socketfd);
            break;
        }
    }
    WSACleanup();

    return 0;
}

unsigned char ip_valida(const char* ip) {
    int cantidad_tokens = 0;

    char* direccion_ip = (char*)malloc(strlen(ip) + 1);
    strcpy(direccion_ip, ip);

    char* token = strtok(direccion_ip, ".");

    while (token != NULL) {
        cantidad_tokens++;

        int cantidad_digitos = 0;
        for (int i = 0; i < strlen(token); i++) {
            if (!isdigit(token[i]))
                return 0;
            cantidad_digitos++;
        }

        if (cantidad_digitos > 3)
            return 0;

        token = strtok(NULL, ".");
    }

    if (cantidad_tokens != 4)
        return 0;

    return 1;
}

void charizard() {
    printf("                 .\"-,.__\n");
    printf("                 `.     `.  ,\n");
    printf("              .--'  .._,'\"-' `.\n");
    printf("             .    .'         `'\n");
    printf("             `.   /          ,'\n");
    printf("               `  '--.   ,-\"'\n");
    printf("                `\"`   |  \\\n");
    printf("                   -. \\, |\n");
    printf("                    `--Y.'      ___.\n");
    printf("                         \\     L._, \\\n");
    printf("               _.,        `.   <  <\\                _\n");
    printf("             ,' '           `, `.   | \\            ( `\n");
    printf("          ../, `.            `  |    .\\`.           \\ \\_\n");
    printf("         ,' ,..  .           _.,'    ||\\l            )  '\".\n");
    printf("        , ,'   \\           ,'.-.`-._,'  |           .  _._`.\n");
    printf("      ,' /      \\ \\        `' ' `--/   | \\          / /   ..\\\n");
    printf("    .'  /        \\ .         |\\__ - _ ,'` `        / /     `.`.\n");
    printf("    |  '          ..         `-...-\"  |  `-'      / /        . `.\n");
    printf("    | /           |L__           |    |          / /          `. `.\n");
    printf("   , /            .   .          |    |         / /             ` `\n");
    printf("  / /          ,. ,`._ `-_       |    |  _   ,-' /               ` \\\n");
    printf(" / .           \\\"`_/. `-_ \\_,.  ,'    +-' `-'  _,        ..,-.    \\`.\n");
    printf(".  '         .-f    ,'   `    '.       \\__.---'     _   .'   '     \\ \\\n");
    printf("' /          `.'    l     .' /          \\..      ,_|/   `.  ,'`     L`\n");
    printf("|'      _.-\"\"` `.    \\ _,'  `            \\ `.___`.'\"`-.  , |   |    | \\\n");
    printf("||    ,'      `. `.   '       _,...._        `  |    `/ '  |   '     .|\n");
    printf("||  ,'          `. ;.,.---' ,'       `.   `.. `-'  .-' /_ .'    ;_   ||\n");
    printf("|| '              V      / /           `   | `   ,'   ,' '.    !  `. ||\n");
    printf("||/            _,-------7 '              . |  `-'    l         /    `||\n");
    printf(". |          ,' .-   ,' ||               | .-.        `.      .'     ||\n");
    printf(" `'        ,'    `\".'    |               |    `.        '. -.'       `'\n");
    printf("          /      ,'      |               |,'    \\-.._,.'/'\n");
    printf("          .     /        .               .       \\    .''\n");
    printf("        .`.    |         `.             /         :_,'.'\n");
    printf("          \\ `...\\   _     ,'-.        .'         /_.-'\n");
    printf("           `-.__ `,  `'   .  _.>----''.  _  __  /\n");
    printf("                .'        /\"'          |  \"'   '_\n");
    printf("               /_|.-'\\ ,\".             '.'`__'-( \\\n");
    printf("                 / ,\"'\"\\,'               `/  `-.|\" \n");
}
