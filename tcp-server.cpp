/*
 * @file
 * TCP Server to recieve some data. Learning.
 */

#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>

/*
 * Libc main function.
 */
int main(int argc, char* argv, char* env) {
  // @see server_class.h
  tcp::server server;
  // Start socket listening.
  int status = server->run();
  return status;
}
