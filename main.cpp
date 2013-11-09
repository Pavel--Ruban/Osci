/*
 * @file
 * TCP Server to receive some data. Learning.
 */

#include "serverClass.h"

/*
 * Libc main function.
 */
int main(int argc, char** argv, char** env) {
  // @see server_class.h
  osci::server *server = new osci::server;
  // Start socket listening.
  int status = server->run();
  return status;
}
