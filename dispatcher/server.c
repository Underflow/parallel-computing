#include <netinet/in.h> 
#include <sys/socket.h> 

#include <event2/bufferevent.h> 
#include <event2/buffer.h> 
#include <event2/listener.h> 
#include <event2/util.h> 
#include <event2/event.h> 

int main()
{

// Send DATA Model    
    typedef struct
    {
        uint8_t client_id;
        char cluster_id;
        char opcode;
        uint8_t size_of;
        char *data;
    }__attribute__((packed)) block; 




    struct sockaddr_in sin;
    


    sin.sin_family= AF_INET;
    sin.sin_port = htons(23);
    
    
    return 0;
}
