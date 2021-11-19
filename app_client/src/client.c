#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <locale.h>
#include <Windows.h>
#include <time.h>

#define CLIENT_SERVER 2500
#define BUFFER_MAX 200

// Se agrega la librería ws2_32 a lista de dependencias
#pragma comment(lib, "ws2_32.lib")

void blastoise();

int main(int argc, const char* argv[]) {
    system("cls");
    blastoise();

    // Para trabajar con caracteres hispanos
    setlocale(LC_ALL, "");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    WSADATA wsa;
    SOCKET socketfd;
    struct sockaddr_in server;
    struct sockaddr_in client;

    int length, n;
    int recv_size;
    char* buf_rx = malloc(512);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        fprintf(stderr, "%ls %d", L"Falló. Código de error: ", WSAGetLastError());
        return 1;
    }

    // Creo el socket
    if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        fprintf(stderr, "No se pudo crear el socket: %d", WSAGetLastError());
        exit(-1);
    }

    // Configuro los parametros del cliente
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_SERVER);
    client.sin_addr.s_addr = INADDR_ANY;
    memset(&(client.sin_zero), 0, 8);

    // Asocio la IP y puerto del server al socket
    if (bind(socketfd, (struct sockaddr*)&client, sizeof(struct sockaddr)) == SOCKET_ERROR) {
        fprintf(stderr, "%ls %d", L"Falló el bind con código de error: ", WSAGetLastError());
        return -1;
    }
    length = sizeof(struct sockaddr_in);

    printf("=========================================================================\n\n");
    printf("%ls", L"Bienvenido!\nEsta es la aplicación Cliente\n\n");
    printf("Autores: Boeri, Israilev, Murcani, Quevedo\n\n");
    printf("=========================================================================\n\n");

    while (1) {
        memset(buf_rx, 0, 512);

        // Recibir una mensaje de un servidor
        if ((recv_size = recvfrom(socketfd, buf_rx, BUFFER_MAX + 2, 0, (struct sockaddr*)&server, &length)) == SOCKET_ERROR) {
            fprintf(stderr, "%ls", L"Recepción fallida.\n");
        } else {
            if (strcmp(buf_rx, "exit\n") == 0)
                break;
            buf_rx[recv_size] = 0;

            struct tm* FechaActual;
            time_t tActual;
            tActual = time(&tActual);
            FechaActual = localtime(&tActual);

            printf("[%02d/%02d/%d-", FechaActual->tm_mday, FechaActual->tm_mon, FechaActual->tm_year + 1900);
            printf("%02d:%02d:%02d]", FechaActual->tm_hour, FechaActual->tm_min, FechaActual->tm_sec);
            printf("[%s:%d]: ", inet_ntoa(server.sin_addr), ntohs(server.sin_port));
            fputs(buf_rx, stdout);
        }
    }
    closesocket(socketfd);

    return 0;
}

void blastoise() {
    printf("                       _\n");
    printf("            _,..-\"\"\"--' `,.-\".\n");
    printf("          ,'      __.. --',  |\n");
    printf("        _/   _.-\"' |    .' | |       ____\n");
    printf("  ,.-\"\"'    `-\"+.._|     `.' | `-..,',--.`.\n");
    printf(" |   ,.                      '    j 7    l \\__\n");
    printf(" |.-'                            /| |    j||  .\n");
    printf(" `.                   |         / L`.`\"\"','|\\  \\\n");
    printf("   `.,----..._       ,'`\"'-.  ,'   \\ `\"\"'  | |  l\n");
    printf("     Y        `-----'       v'    ,'`,.__..' |   .\n");
    printf("      `.                   /     /   /     `.|   |\n");
    printf("        `.                /     l   j       ,^.  |L\n");
    printf("          `._            L       +. |._   .' \\|  | \\\n");
    printf("            .`--...__,..-'\"\"'-._  l L  \"\"\"    |  |  \\\n");
    printf("          .'  ,`-......L_       \\  \\ \\     _.'  ,'.  l\n");
    printf("       ,-\"`. / ,-.---.'  `.      \\  L..--\"'  _.-^.|   l\n");
    printf(" .-\"\".'\"`.  Y  `._'   '    `.     | | _,.--'\"     |   |\n");
    printf("  `._'   |  |,-'|      l     `.   | |\"..          |   l\n");
    printf("  ,'.    |  |`._'      |      `.  | |_,...---\"\"\"\"\"`    L\n");
    printf(" /   |   j _|-' `.     L       | j ,|              |   |\n");
    printf("`--,\"._,-+' /`---^..../._____,.L',' `.             |\\  |\n");
    printf("   |,'      L                   |     `-.          | \\j\n");
    printf("            .                    \\       `,        |  |\n");
    printf("             \\                __`.Y._      -.     j   |\n");
    printf("              \\           _.,'       `._     \\    |  j\n");
    printf("              ,-\"`-----\"\"\"\"'           |`.    \\  7   |\n");
    printf("             /  `.        '            |  \\    \\ /   |\n");
    printf("            |     `      /             |   \\    Y    |\n");
    printf("            |      \\    .             ,'    |   L_.-')\n");
    printf("             L      `.  |            /      ]     _.-^._\n");
    printf("              \\   ,'  `-7         ,-'      / |  ,'      `-._\n");
    printf("             _,`._       `.   _,-'        ,',^.-            `.\n");
    printf("          ,-'     v....  _.`\"',          _:'--....._______,.-'\n");
    printf("        ._______./     /',,-'\"'`'--.  ,-'  `.\n");
    printf("                 \"\"\"\"\"`.,'         _\\`----...' mh\n");
    printf("                        --------\"\"'\n");
    printf("\n");
    printf("\n");
}
