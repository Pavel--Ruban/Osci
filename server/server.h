#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>

/**
 * tcp namespace to avoid library name conflicts.
 */
namespace osci {
  class server;
}

/**
 * Provides server class for manager application.
 */
class osci::server {
  private:
    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    int socketfd ; // The socket descripter
    int yes;

  public:
    // Method to start server & enter to loop.
    int run();
};
