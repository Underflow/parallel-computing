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


struct buffer_rec
{
    size_t size;
    char *buffer;
};
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


        return dest;
    }
    return NULL;
}

void proceed_task(char *buffer)
{
    printf("%s\n", buffer + sizeof(struct mlc_packet_header));
    /*
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
    */
}

void rec_buffer(int socket,struct buffer_rec b)
{
    char *temp;
    size_t n = 0;
    b.size = 0;
    b.buffer = malloc(1024);
    
    while(n = recv(socket,temp,strlen(temp)) > 0)
    {
        if(n>
        strcpy(b.buffer+b.size,temp);


    }
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
    char buffer_ask[1024];


    struct sockaddr_in server;
    struct mlc_packet_header header;
    struct buffer_rec buffer;



    sock = socket(AF_INET , SOCK_STREAM , 0);
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);

    if(connect(sock , (struct sockaddr *)&server , sizeof(server)) == -1)
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
    header.size_of = strlen(buffer_ask) + sizeof(struct mlc_packet_header);

    // Boucle tant que 1, à l'avenir paramètre à changer jusqu'à ce qu'il
    // recoive l'odre de s'arreter. 
    while(1)
    {


        sleep(1);

        printf("Demande de tâches ...\n");
        send(sock, (char*)&header, sizeof(struct mlc_packet_header), 0);
        send(sock, buffer_ask, strlen(buffer_ask), 0);

        rec_buffer(sock,buffer);
    }

    return 0;
}

