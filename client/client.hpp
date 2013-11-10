/**
 * Provides client class to send request to server.
 *
 * @author Pavel Ruban
 * @contact http://pavelruban.org
 */

#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>      // Needed for the socket functions
#include <gtk/gtk.h>      // Needed for the socket functions
class client {
  public:
    char *host;
    char *msg;

    const char *port;
    char status;
    int socketfd ; // The socket descripter

    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    /**
     * Creates & bind socket & open tunnel to another socket.
     *
     * @param
     * @return status
     */
    char connect();

    /**
     * Sends string to server.
     * @param char *msg message body
     * @return server response
     */
    char *send(char *msg);

    /**
     * Closes opend socket.
     * @return status
     */
    int close();
};
