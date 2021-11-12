#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT            3550    // Puerto de conexion
#define MAX_TAMA_DATO   100     // Tamaño maximo en bytes a transmitir

int main(int argc, char const *argv[]) {
    int fd, numbytes;                  //Descriptores de archivo
    char buf[MAX_TAMA_DATO], ip[100];  //Buffer temporario
    
    struct hostent *he;
    struct sockaddr_in servidor;  //Info de la direccion del servidor
    
    printf("Cliente \nHost o Dirección IP: ");
    scanf("%s", &ip);
    
    if ((he = gethostbyname(ip)) == NULL) {
        //Puede resolver el nombre o ip?
        printf("Error en Gethostbyname()\n");
        exit(-1);
        
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("Error en Socket()\n");
            exit(-1);
        }

        servidor.sin_family = AF_INET;
        servidor.sin_port = htons(PORT);
        servidor.sin_addr = *((struct in_addr *)he->h_addr);
        bzero(&(servidor.sin_zero), 8);
        
        if (connect(fd, (struct sockaddr *)&servidor, sizeof(struct sockaddr)) < 0) {
            printf("Error en Connect()");
            exit(-1);
        }
        
        if ((numbytes = recv(fd, buf, MAX_TAMA_DATO, 0)) < 0) {
            printf("Error en recv()\n");
            exit(-1);
        }
        
        buf[numbytes] = '\0';
        printf("Mensaje del servidor: %s\n", buf);
        close(fd);
    }
}