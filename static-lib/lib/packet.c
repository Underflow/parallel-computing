#include <stdint.h>
#include <event2/bufferevent.h>
#include <stdlib.h>
#include <stdio.h>
#include "packet.h"

/*
** Cette fonction génère le packet.
** A finir.
*/
void send_packet(uint8_t cluster_id,
                  uint8_t opcode,
                  char *data,
                  int size_of,
                  struct bufferevent *bev)
{
    struct mlc_packet_header header;
    // L'id du client est à 0, packet émis par le serveur
    header.client_id = 0;
    header.opcode = opcode;
    header.cluster_id = cluster_id;
    header.size_of = sizeof(struct mlc_packet_header) + size_of;

    // Envoi du packet
    bufferevent_write(bev, (char*)&header, sizeof(struct mlc_packet_header));
    if(size_of)
        bufferevent_write(bev, data, size_of);
}

