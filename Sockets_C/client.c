#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>

int puerto = 7200;

int main(int argc, char const *argv[])
{
   if(argc !=2 ){
       printf("./cleinte.out <message>");
       return 0;
   }
    /*
         struct sockaddr_in, la cual nos ayuda a hacer referencia a los elementos del socket genérico
    */
    struct sockaddr_in msg_to_server_addr, client_addr;
    int s;
    char messge[20],response[20]; //array con un tamaño suficiente que garantice que es mayor o igual que la cadena a messger
    

    s = socket(AF_INET, SOCK_DGRAM, 0);
    /* rellena la dirección del servidor */
    bzero((char *)&msg_to_server_addr, sizeof(msg_to_server_addr));
    //Rellenamos loe elemtnos de la estructura genérica de socket
    msg_to_server_addr.sin_family = AF_INET;   
    msg_to_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    msg_to_server_addr.sin_port = htons(puerto);

    /* rellena la direcciòn del cliente*/
    bzero((char *)&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    /*cuando se utiliza por numero de puerto el 0, el sistema se encarga de asignarle uno */
    client_addr.sin_port = htons(0);
    bind(s, (struct sockaddr *)&client_addr, sizeof(client_addr));

    //Se relena el mensaje
    strcpy(messge, argv[1]);
    sendto(s, (char *)messge, sizeof(messge), 0, (struct sockaddr *)&msg_to_server_addr, sizeof(msg_to_server_addr));

    /* se bloquea esperando respuesta */
    recvfrom(s, (char *)&response, sizeof(response), 0, NULL, NULL);
    // printf("puerto del remitente 127.0-0.1");
    printf("%s\n", response);

    close(s);
}
