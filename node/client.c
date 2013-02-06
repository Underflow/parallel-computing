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
    double client_id;
    uint8_t cluster_id;
    uint8_t opcode;
    int size_of;
}__attribute__((packed));


int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;

    sock = socket(AF_INET , SOCK_STREAM , 0);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(9995);

    connect(sock , (struct sockaddr *)&server , sizeof(server));
    char *data="BLABLABLA";
    struct mlc_packet_header header;
    header.client_id = 42;
    header.opcode = 2;
    header.cluster_id = 10;
    header.size_of = sizeof(struct mlc_packet_header) + strlen(data);
    printf("%d:%d\n", sizeof(struct mlc_packet_header), header.size_of);
    send(sock, (char*)&header, sizeof(struct mlc_packet_header), 1);
    send(sock, data, strlen(data), 1);
    /*
    recv(sock , server_reply , 18 , 0);
    test=(struct mlc_packet_header*)server_reply;
   

    // RECEPTION DE LA STRUCTURE 
    printf("Client_id : %X\n",test->client_id);
    printf("CLuster_id : %d\n",test->cluster_id);
    printf("Opcode : %d\n",test->opcode);
    printf("Size_of : %d\n",test->size_of);
    */
    return 0;
}

