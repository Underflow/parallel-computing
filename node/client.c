#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <event.h>


// Send DATA Model
struct mlc_packet_header
{
    uint8_t client_id[8];
    uint8_t cluster_id;
    uint8_t opcode;
    uint8_t size_of[8];
}__attribute__((packed));


int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    struct mlc_packet_header *test;

    test=malloc(sizeof(struct mlc_packet_header)); 
    
    char server_reply[2000];

    sock = socket(AF_INET , SOCK_STREAM , 0);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(9995);

    connect(sock , (struct sockaddr *)&server , sizeof(server));
    recv(sock , server_reply , 18 , 0);
    test=(struct mlc_packet_header*)server_reply;
   

    // RECEPTION DE LA STRUCTURE 
    printf("Client_id : %d\n",test->client_id[0]);
    printf("CLuster_id : %d\n",test->cluster_id);
    printf("Opcode : %d\n",test->opcode);
    printf("Size_of : %d\n",test->size_of[0]);

    return 0;
}

