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

#include "packet.h"
#include "task_list.h"
#include "server.h"
#include "schedulding.h"

static const int PORT = 4242;

int main()
{
    struct event_base *base;
    struct evconnlistener *listener;
    struct event *signal_event;
    struct sockaddr_in sin;

    task_list tlist = init_tasks(100, 0);

    
    base = event_base_new();
    if (!base) {
        fprintf(stderr, "Could not initialize libevent!\n");
        return 1;
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    listener = evconnlistener_new_bind(base, listener_connection_event, tlist,
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


    return 0;
}

/*
** Cette méthode traite les données reçues après formatage.
*/
void handle_packet(struct mlc_packet_header header, 
                   char* data,
                   struct bufferevent *bev,
                   task_list tlist)
{
    task t;
    switch (header.opcode)
    {
        case 1:
            t = next_tlist(tlist);
            send_packet(header.cluster_id, 2, t->task, strlen(t->task), bev);
            /* association tâche/noeud
            pour pouvoir retrouver une tâche (afin de la terminer plus tard,
            il faut d'abord associer un client_id à une tâche.
            Pour l'opcode 0x03, on end_task() la tache correspondante au
            client_id
            */
            break;
        case 2:
            perror("Error : this opcode is not implemented");
        case 3:
            printf("Received result : %s", data);
            break;
        default:
            break;
    }
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
    bufferevent_setcb(bev, read_event, NULL, client_connection_event, user_data);
    bufferevent_enable(bev, EV_READ);
}



/*
** Callback de lecture
** Cette méthode est appélée lorsque le serveur reçoit les données d'un des
** clients.
*/
void read_event(struct bufferevent *bev, void *user_data)
{

    task_list tlist = (task_list)user_data;

    struct evbuffer *buffer = bufferevent_get_input(bev);

    // On regarde si on a reçu au moins le header
    while(evbuffer_get_length(buffer) >= sizeof(struct mlc_packet_header))
    {
        struct mlc_packet_header header;
        // Le header est complet, on l'extrait
        evbuffer_copyout(buffer, (void*)&header, sizeof(struct mlc_packet_header));
        // On regarge la taille des données dans le header afin de déterminer
        //si la totalité des données ont été reçues
        
        if(evbuffer_get_length(buffer) >= header.size_of)
        {
            size_t data_size = header.size_of - sizeof(struct mlc_packet_header);
            char *data = calloc(1, data_size);
            // On supprime le header du buffer
            evbuffer_drain(buffer, sizeof(struct mlc_packet_header));
            // On extrait les données du buffer
            evbuffer_remove(buffer, (void*)data, data_size); 
            // On traite le packet reçu, complet
            handle_packet(header, data, bev, tlist);
        }
        else
            break;
    }

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
    printf("Exiting server : 2 sec.\n");
    event_base_loopexit(base, &delay);
}
