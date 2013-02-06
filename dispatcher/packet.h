/*
** Header des packets client/serveur
** Structure des packets [HEADER:DATA]
*/
struct mlc_packet_header
{
    double client_id;
    uint8_t cluster_id;
    uint8_t opcode;
    int size_of;
}__attribute__((packed));

void send_packet(char cluster_id,
                  uint8_t opcode,
                  char *data,
                  int size_of,
                  struct bufferevent *bev);

