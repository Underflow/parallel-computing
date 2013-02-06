/*
** Header des packets client/serveur
** Structure des packets [HEADER:DATA]
*/
struct mlc_packet_header
{
    double client_id;
    char cluster_id;
    uint8_t opcode;
    double size_of;
}__attribute__((packed));
