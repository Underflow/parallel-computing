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

//static struct { int freq; int len; unsigned long delay; } freqs[] = {
//#include "notes.def"
//};


int main()
{
    struct event_base *base;
    struct evconnlistener *listener;
    struct event *signal_event;
    struct sockaddr_in sin;
    pargs arg_event;

    arg_event=malloc(sizeof(struct args));
    arg_event->tlist = init_tasks(1000, 0);
    arg_event->h = NULL; // Ne pas modifier, indispensable


    base = event_base_new();
    if (!base) {
        fprintf(stderr, "Could not initialize libevent!\n");
        return 1;
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

    free_tlist(arg_event->tlist);

    return 0;
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
                if(return_task_from_link(&(arg->h),header.client_id) == -1)
                {
                    t = next_tlist(arg->tlist);
                    add_new_link(&(arg->h),header.client_id,t->id);
                    send_packet(header.cluster_id, 2,t->task,strlen(t->task),bev);
                }
                /*struct timeval  tv;
                  gettimeofday(&tv, NULL);

                  double time_in_mill = 
                  (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
                  static double old_time = 0;

                  static int note = 0;
                  note = (note + 1) % (sizeof (freqs) / sizeof (freqs[0]));

                  if(old_time + freqs[note].delay < time_in_mill)
                  {
                  old_time = time_in_mill;    
                  t = next_tlist(tlist);
                  send_packet(header.cluster_id, 2, t->task, strlen(t->task), bev);
                  }
                  else
                  {
                  send_packet(header.cluster_id, 2, NULL, 0, bev);*/



            }




            /* association tâche/noeud
               pour pouvoir retrouver une tâche (afin de la terminer plus tard,
               il faut d'abord associer un client_id à une tâche.
               Pour l'opcode 0x03, on end_task() la tache correspondante au
               client_id
               */
            break;
                case 2:
            perror("Error : this opcode is not implemented");
            break;
                case 3:
            if(strlen(data))
            {
                printf("Received result : %s\n", data);
                int result=atoi(data);
                if(result==1)
                {
               system("pkill dispatcher");
                }
            end_task(return_task_from_link(&(arg->h),header.client_id),arg->tlist);
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
