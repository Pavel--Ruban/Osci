#include <boost/asio.hpp> 
#include <string> 
#include <boost/thread.hpp> 
#include <iostream> 

boost::asio::io_service io_service; 
boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 1090); 
boost::asio::ip::tcp::socket sock(io_service); 
std::string data = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!"; 

void write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred);

void accept_handler(const boost::system::error_code &ec) 
{ 
  if (ec) {
    std::cout << "dasdasd";
  }
  else { 
    boost::asio::async_write(sock, boost::asio::buffer(data), write_handler); 
  } 
} 

void write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) { 
  if (ec) {
    std::cout << "error" << std::endl;
  }
  else { 
    std::cout << "waiting for a new connection..." << std::endl;
    //acceptor.listen(); 
    //acceptor.async_accept(sock, accept_handler); 
    //io_service.run(); 
  } 
} 

void processConection() {
  std::cout << "thread is created..." << std::endl;
}

int main() 
{ 
  boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint); 
  acceptor.listen(); 
  while (1) {
    // Create socket
    SmartSocket sock(new boost::asio::ip::tcp::socket(io_service));
    // Waiting for client
//    acceptor.accept(*sock);
    acceptor.async_accept(*sock, accept_handler); 
    cout << "Client connected" << endl;
  }
  io_service.run(); 
} 

