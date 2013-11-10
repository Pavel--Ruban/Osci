/**
 * Provides client class to send request to server.
 *
 * @author Pavel Ruban
 * @contact http://pavelruban.org
 */
#include "client.hpp"

/**
 * Creates & bind socket & open tunnel to another socket.
 *
 * @param
 * @return status
 */
char client::connect() {
  /** The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
   * to by hints must contain either 0 or a null pointer, as appropriate." When a struct
   * is created in C++, it will be given a block of memory. This memory is not necessary
   * empty. Therefor we use the memset function to make sure all fields are NULL.
   */
  memset(&this->host_info, 0, sizeof this->host_info);
  g_print("Setting up the structs...\n");

  this->host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
  this->host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

  // Now fill up the linked list of this->host_info structs with google's address information.
  this->status = getaddrinfo(this->host, this->port, &this->host_info, &this->host_info_list);

  // getaddrinfo returns 0 on succes, or some other value when an error occured.
  // (translated into human readable text by the gai_gai_strerror function).
  if (this->status != 0) {
    std::cout << "getaddrinfo error" << gai_strerror(status) ;
    return this->status;
  }

  std::cout << "Creating a socket..."  << std::endl;

  this->socketfd = socket(
      this->host_info_list->ai_family,
      this->host_info_list->ai_socktype,
      this->host_info_list->ai_protocol
      );

  if (this->socketfd == -1) {
    std::cout << "socket error " ;
    return this->socketfd;
  }
  std::cout << "Connect()ing..."  << std::endl;
  this->status = ::connect(this->socketfd, this->host_info_list->ai_addr, this->host_info_list->ai_addrlen);
  if (this->status == -1)  std::cout << "connect error" ; return this->status;
}

/**
 * Sends string to server.
 * @param char *msg message body
 * @return server response
 */
char *client::send(char *msg) {
  std::cout << "sending message..."  << std::endl;
  int len;
  ssize_t bytes_sent;
  len = strlen(msg);
  bytes_sent = ::send(this->socketfd, msg, len, 0);
  std::cout << "Waiting to recieve data..."  << std::endl;
  ssize_t bytes_recieved;
  char incoming_data_buffer[1000];
  bytes_recieved = recv(this->socketfd, incoming_data_buffer,1000, 0);
  // If no data arrives, the program will just wait here until some data arrives.
  if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
  if (bytes_recieved == -1) std::cout << "recieve error!" << std::endl ;
  std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
//  std::cout << incoming_data_buffer << std::endl;

  return incoming_data_buffer;
}

/**
 * Closes opend socket.
 * @return status
 */
int client::close() {
  std::cout << "Receiving complete. Closing socket..." << std::endl;
  freeaddrinfo(this->host_info_list);
  ::close(this->socketfd);
}
