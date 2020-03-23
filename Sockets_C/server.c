#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>

int puerto = 7200;

int main(void)
{
   char response[22] = "HI NICE TOO MEET YOU", greeting[22];
   int s, res, client_length;
   struct sockaddr_in server_addr, msg_to_client_addr;
   
   s = socket(AF_INET, SOCK_DGRAM, 0);
   
   /* se asigna una direccion al socket del servidor*/
   bzero((char *)&server_addr, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(puerto);
   /*
      Su función esencial es asociar un socket con un puerto (de nuestra máquina). Análogamente socket(), devolverá -1 en caso de error.
   */
   if(bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr))==-1){
      printf("ERROR TO CONNECT!");
      return 0;
   }
   
   client_length = sizeof(msg_to_client_addr);
   while(1) {
      /*
         Recibe infromacion y devuele el númerod ebytes leidos
         1 - Socket por el cual se recibe la infromación
         2 - Mensaje que se recibe
         3 - numero de bytes que se pueden recibir, es decir el tamaño del mensaje
         4 - 0
         5 - Dirección de la estructura socket del que sehan recibido lo datos
         6 - Espacio en bytes que ocupa dicha estructura del socekt
      */
      recvfrom(s, (char *) greeting, sizeof(greeting), 0, (struct sockaddr *)&msg_to_client_addr, &client_length);
      printf("Received >: %s",greeting);
      /* envía la petición al cliente. La estructura msg_to_client_addr contiene la dirección socket del cliente */
      sendto(s, (char *)&response, sizeof(response), 0, (struct sockaddr *)&msg_to_client_addr, client_length);
   }
}
