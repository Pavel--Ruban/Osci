#include <boost/asio.hpp> 
#include <boost/array.hpp> 
#include <boost/thread.hpp> 
#include <iostream> 
#include <string> 

boost::asio::io_service io_service; 
boost::asio::ip::tcp::resolver resolver(io_service); 
boost::asio::ip::tcp::socket sock(io_service); 
boost::array<char, 4096> buffer; 

void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) 
{ 
  if (!ec) 
  { 
      std::cout << "========= NEW DATA IS RECEIVED ==============" << std::endl << std::string(buffer.data(), bytes_transferred) << std::endl; 
      std::cout << "========= NEW DATA SECTION END ==============" << std::endl;
      sock.async_read_some(boost::asio::buffer(buffer), read_handler); 
  } 
} 

void connect_handler(const boost::system::error_code &ec) 
{ 
  if (!ec) 
  { 
    boost::asio::write(sock, boost::asio::buffer("GET / HTTP 1.1\r\r\n\r\n")); 
    sock.async_read_some(boost::asio::buffer(buffer), read_handler); 
  } 
} 

void resolve_handler(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it) 
{ 
  if (!ec) 
  { 
    sock.async_connect(*it, connect_handler); 
  } 
} 

void run() { 
  io_service.run(); 
}

int main() 
{ 
  boost::asio::ip::tcp::resolver::query query("www.pavelruban.org", "80"); 
  resolver.async_resolve(query, resolve_handler); 

  boost::asio::ip::tcp::resolver::query query2("www.drupal.org", "80"); 
  resolver.async_resolve(query2, resolve_handler); 

  boost::thread thread1(run); 
  boost::thread thread2(run); 
  thread1.join(); 
  thread2.join(); 
} 
