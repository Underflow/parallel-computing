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

#include "hashtab.h"
#include "uthash.h"
#include "packet.h"
#include "task_list.h"
#include "server.h"
#include "schedulding.h"

static const int PORT = 4242;

void* tsk_gen_ptr;
void* get_result_ptr;

typedef void(*fvoidptr)(int, char*);

void init(void* tsk_gen, void* get_reslt)
{
    struct event_base *base;
    struct evconnlistener *listener;
    struct event *signal_event;
    struct sockaddr_in sin;
    pargs arg_event;

    tsk_gen_ptr = tsk_gen;
    get_result_ptr = get_reslt;

    arg_event=malloc(sizeof(struct args));
    arg_event->tlist = init_tasks(100, 0);
    arg_event->h = NULL;

    base = event_base_new();
    if (!base) {
        fprintf(stderr, "Could not initialize libevent!\n");
        return;
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    listener = evconnlistener_new_bind(base, listener_connection_event, (void*)arg_event,
                                       LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
                                       (struct sockaddr*)&sin,
                                       sizeof(sin));

    if (!listener) {
        fprintf(stderr, "Could not create a listener!\n");
        return;
    }

    signal_event = evsignal_new(base, SIGINT, close_event, (void *)base);

    if (!signal_event || event_add(signal_event, NULL)<0) {
        fprintf(stderr, "Could not create/add a signal event!\n");
        return;
    }

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_free(signal_event);
    event_base_free(base);

    free_tlist(arg_event->tlist);
}

/*
** Cette méthode traite les données reçues après formatage.
*/
void handle_packet(struct mlc_packet_header header, 
                   char* data,
                   struct bufferevent *bev,
                   pargs arg)
{
    task t;
    switch (header.opcode)
    {
        case 1:
            {
                t = next_tlist(arg->tlist);
                add_new_link(&(arg->h),header.client_id,t->id);
                send_packet(header.cluster_id, 2,t->task,strlen(t->task),bev);
            }
            break;
                case 2:
            perror("Error : this opcode is not implemented");
            break;
                case 3:
                {
                    fvoidptr get_result_fun = (fvoidptr)get_result_ptr;
                    int tid = return_task_from_link(&(arg->h), header.client_id);
                    get_result_fun(tid, data);
                    end_task(tid,arg->tlist);
                    delete_link(&(arg->h),header.client_id);
                }
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
                handle_packet(header, data, bev, (pargs)user_data);
                free(data);
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
        struct timeval delay = { 0, 0 };
        printf("Exiting server : 2 sec.\n");
        event_base_loopexit(base, &delay);
    }
