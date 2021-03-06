typedef struct args *pargs;
struct args
{
    task_list tlist;
    struct hash_tab *h;
};

void listener_connection_event(struct evconnlistener *listener,
                               evutil_socket_t fd,
                               struct sockaddr *sa,
                               int socklen,
                               void *user_data);
void read_event(struct bufferevent *bev, void *user_data);
void client_connection_event(struct bufferevent *bev,
                             short events,
                             void *user_data);
void close_event(evutil_socket_t sig, short events, void *user_data);
void handle_packet(struct mlc_packet_header header, 
                   char* data,
                   struct bufferevent *bev,
                   pargs arg);
