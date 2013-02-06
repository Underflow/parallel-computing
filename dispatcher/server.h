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
