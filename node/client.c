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


struct string_packet
{
    size_t size;
    size_t length;
    char *buffer;
};


struct mlc_packet_header create_packet(double client_id,uint8_t cluster_id,uint8_t opcode,char *data)
{
	struct mlc_packet_header header;
	header.client_id=client_id;
	header.cluster_id=cluster_id;
	header.opcode=opcode;
	header.size_of= strlen(data) + sizeof(struct mlc_packet_header);

	return header;
}	

void proceed_task(struct mlc_packet_header *header,char *buffer)
{
    // Decoupe du data et cast en char*

    printf("Traitement ...\n");
    // Affichage de la struct
    printf("Client_id : %f\n",header->client_id);
    /*printf("Cluster_id : %d\n",header->cluster_id);
    printf("Opcode : %d\n",header->opcode);
    printf("Size_of : %d\n",header->size_of);

    // Affichage de la data;
    printf("Data : %s\n\n",buffer);*/
    switch(header->opcode)
	{
		case 2:
		    system(buffer);
		    break;
		default:
		    ;
	}
}


struct string_packet append_buffer(struct string_packet str_p,int length,char* src)
{

        if(str_p.length > str_p.size)
        {
            str_p.size *= 2;
            str_p.buffer = realloc(str_p.buffer,str_p.size);
        }

        for(int i=0 ; i<length; i++)
            str_p.buffer[str_p.length + i] = src[i];

        str_p.length += length;
        return str_p;
}

struct string_packet drain_buffer(struct string_packet str_p, size_t n)
{
    char* new=malloc(str_p.size);

    for(int i=0; i < (str_p.length-n); i++)
        new[i] = str_p.buffer[i + n];
    str_p.buffer = new;

    return str_p;
}

char* strncpy_buffer(char *dest,const char *src,size_t n)
{
    size_t i;
    for(i = 0; i < n; i++)
        dest[i] = src[i];
    return dest;
}

struct string_packet check_rec(struct string_packet str_p)
{
    if(str_p.length >= sizeof(struct mlc_packet_header))
    {
        struct mlc_packet_header *header;

        char *header_str=malloc(sizeof(struct mlc_packet_header));
        header_str = strncpy_buffer(header_str,str_p.buffer,sizeof(struct mlc_packet_header));
        
        header = (struct mlc_packet_header*)header_str;
        if(str_p.length >= header->size_of)
        {
            str_p = drain_buffer(str_p,sizeof(struct mlc_packet_header));
            char *data=malloc(header->size_of);
            data = strncpy(data,str_p.buffer,header->size_of);
            str_p = drain_buffer(str_p,header->size_of);
            str_p.length -= header->size_of;
            proceed_task(header,data);
        }
    }
        return str_p;
}

void rec_buffer(int socket)
{
    // Buffer du recv
    char *buffer=malloc(1024);

    // Packet entier
    struct string_packet str_p;
    str_p.size=1024;
    str_p.length=0;
    str_p.buffer=malloc(1024);

    int length=0;

    while((length = recv(socket,buffer,1024,0))>0) 
    {
        str_p = append_buffer(str_p,length,buffer);
        str_p = check_rec(str_p);
        if(str_p.length <= 0)
            break;
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

    if(argc != 2)
    {
        printf("Argument 1 : IP\n");
        return 0;
    }

    char *server_ip = argv[1];
    int server_port = 4242;

    int sock;
    char buffer_ask[1024];

    struct sockaddr_in server;
    struct mlc_packet_header header;



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
    header = create_packet(1,2,1,buffer_ask);

    // Boucle tant que 1, à l'avenir paramètre à changer jusqu'à ce qu'il
    // recoive l'odre de s'arreter. 
    while(1)
    {
        sleep(1);

        printf("Demande de tâches ...\n");
        send(sock, (char*)&header, sizeof(struct mlc_packet_header), 0);
        send(sock, buffer_ask, strlen(buffer_ask), 0);
        rec_buffer(sock);
    }

    return 0;
}

