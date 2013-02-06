#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <event.h>


// Send DATA Model
struct mlc_packet_header
{
    double client_id;
    uint8_t cluster_id;
    uint8_t opcode;
    int size_of;
}__attribute__((packed));

/*
** Fonction de découpe (substring)
*/

char *substr(char *src,int pos,int len) 
{ 
  char *dest=NULL;                        
  if (len>0) 
  {                  
    dest = calloc(len+1, 1);      
    if(NULL != dest) 
        strncat(dest,src+pos,len);            
    
  }                                       
  return dest;      
} 

void proceed_task(char *buffer)
{
    struct mlc_packet_header *header;

    // Decoupe du header et cast en structure
    header = (struct mlc_packet_header*)
        substr(buffer, 0, sizeof(struct mlc_packet_header));

    // Decoupe du data et cast en char*
    char *data = substr(buffer,sizeof(struct mlc_packet_header), strlen(buffer)-sizeof(struct mlc_packet_header));
    
    printf("Traitement ...\n");
    // Affichage de la struct
    printf("Client_id : %f\n",header->client_id);
    printf("CLuster_id : %d\n",header->cluster_id);
    printf("Opcode : %d\n",header->opcode);
    printf("Size_of : %d\n",header->size_of);

    // Affichage de la data;
    printf("Data : %s\n\n",data);


    // Vide entièrement le buffer une fois que la tâche a été effectuer
    memset(&buffer[0], 0, sizeof(buffer));

}

/* 
** Pour trasnformer le client en bibliothèque il suffirat de 
** donner 2 arguments à cette fonctions : 
** - IP du serveur
** - Port à utiliser
*/

int main(int argc , char *argv[])
{

    if(argc != 3)
    {
        printf("Argument 1 : IP\n");
        printf("Argument 2 : PORT\n");
        return 0;
    }

    char *server_ip = argv[1];
    int server_port = atoi(argv[2]);

    int sock;
    char buffer_rec[1024];
    char buffer_ask[1024];
    struct sockaddr_in server;
    struct mlc_packet_header header;




    sock = socket(AF_INET , SOCK_STREAM , 0);
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);

    if(connect(sock , (struct sockaddr *)&server , sizeof(server) == -1))
    {
        printf("Le serveur n'a pas réussi à être atteint :\n    IP : %s\n    PORT : %d\n", server_ip, server_port);
        return 0;
    }


    // La structure ainsi que la data pour demander une tâche est
    // constamment la même, ici c'est un test qui est fait

    strcpy(buffer_ask, "blablabla");
    header.client_id = 1;
    header.cluster_id = 2;
    header.opcode = 3;
    header.size_of = 4;

    // Boucle tant que 1, à l'avenir paramètre à changer jusqu'à ce qu'il
    // recoive l'odre de s'arreter. Il y a un timeout de 20 secondes si le
    // serveur n'envoie rien. Il faudrait insérer un timeout de 20 secondes à
    // la place du sleep(20) mais ce n'est pas standart.

    while(1)
    {

        printf("Demande de tâches ...\n");
        send(sock, (char*)&header, sizeof(struct mlc_packet_header), 0);
        send(sock, buffer_ask, strlen(buffer_ask), 0);

        if(recv(sock, buffer_rec, sizeof(buffer_rec), MSG_DONTWAIT) > 0)
            proceed_task(buffer_rec);
        else
            sleep(20);
            
    }

    return 0;
}

