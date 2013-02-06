#include <netinet/in.h> 
#include <sys/socket.h> 
#include <stdlib.h>


#include <event2/bufferevent.h> 
#include <event2/buffer.h> 
#include <event2/listener.h> 
#include <event2/util.h> 
#include <event2/event.h> 

#include <errno.h>
#include <string.h>
#include <signal.h>

#include "server.h"
#include "packet.h"

static const int PORT = 9995;

int main()
{
    struct event_base *base;
    struct evconnlistener *listener;
    struct event *signal_event;
    struct sockaddr_in sin;
    
    char *str=(char*)new;
    base = event_base_new();
    if (!base) {
        fprintf(stderr, "Could not initialize libevent!\n");
        return 1;
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    listener = evconnlistener_new_bind(base, listener_connection_event, str,
                                       LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
                                       (struct sockaddr*)&sin,
                                       sizeof(sin));

    if (!listener) {
        fprintf(stderr, "Could not create a listener!\n");
        return 1;
    }

    signal_event = evsignal_new(base, SIGINT, close_event, (void *)base);

    if (!signal_event || event_add(signal_event, NULL)<0) {
        fprintf(stderr, "Could not create/add a signal event!\n");
        return 1;
    }

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_free(signal_event);
    event_base_free(base);

    printf("done\n"); 

    return 0;
}



/*
** Callback de connection du listener
** Cette méthode est appélée lorsqu'un client se connecte au serveur (i.e : 
** quand le listener reçoit une connection).
*/
void listener_connection_event(struct evconnlistener *listener,
                               evutil_socket_t fd,
                               struct sockaddr *sa,
                               int socklen,
                               void *user_data)
{
    struct event_base *base = evconnlistener_get_base(listener);
    struct bufferevent *bev;

    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev) {
        fprintf(stderr, "Error constructing bufferevent!");
        event_base_loopbreak(base);
        return;
    }
    bufferevent_setcb(bev, NULL, write_event, client_connection_event, NULL);
    bufferevent_enable(bev, EV_WRITE);
    bufferevent_disable(bev, EV_READ);
    bufferevent_write(bev,(char*)user_data, 18);
}


/* 
** Callback d'écriture
** Cette fonction est appelée lorsque le serveur envoie des données à un
** client.
*/
void write_event(struct bufferevent *bev, void *user_data)
{
    struct evbuffer *output = bufferevent_get_output(bev);
    if (evbuffer_get_length(output) == 0) {
        bufferevent_free(bev);
    }
}

/*
** Callback de lecture
** Cette méthode est appélée lorsque le serveur reçoit les données d'un des
** clients.
*/

void read_event(struct bufferevent *bev, void *user_data)
{

}

/*
** Callback de connection des clients
** Cette méthode est appelée lorsqu'un événement se produit concernant la
** connection des clients connectés
*/
void client_connection_event(struct bufferevent *bev,
                             short events,
                             void *user_data)
{
    if (events & BEV_EVENT_EOF) {
        printf("Connection closed.\n");
    } else if (events & BEV_EVENT_ERROR) {
        printf("Got an error on the connection: %s\n",
               strerror(errno));/*XXX win32*/
    }
    /* None of the other events can happen here, since we haven't enabled
     * timeouts */
    bufferevent_free(bev);
}


/*
** Callback de fermeture du serveur
** Cette méthode est appelée à la fermeture du serveur.
*/
void close_event(evutil_socket_t sig, short events, void *user_data)
{
    struct event_base *base = user_data;
    struct timeval delay = { 2, 0 };
    printf("Exiting server : 2 sec");
    event_base_loopexit(base, &delay);
}
