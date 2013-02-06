#include "packet.h"


/*
** Cette fonction génère le packet.
** A finir.
*/
char* forge_packet(struct mlc_packet_header, char* data)
{
    new=malloc(sizeof(struct mlc_packet_header)); 
    new->client_id[0]='1';
    new->cluster_id=10;
    new->opcode=5;
    new->size_of[0]='1';
    
    return NULL;
}
