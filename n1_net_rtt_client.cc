#include "utils_tcp.h"
#include "utils.h"
#include <string.h>

#define PORT "3490" // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once


int main(int argc, char *argv[]) {
    int numbytes;
    char buf[MAXDATASIZE];

    // check args
    if (argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    // int state = STATE_INIT;

    // connect tcp
    char port[] = PORT;
    int sockfd = tcp_client_connect(argv[1], port);

    // receive message
    numbytes = tcp_receive(sockfd, buf);

    // print message
    buf[numbytes] = '\0';
    printf("client: received '%s'\n", buf);

    // clean up
    tcp_shutdown_close(sockfd);

    return 0;
}
