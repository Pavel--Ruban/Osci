#include "../server/asyncServer.hpp"
#include "window.hpp"

void destroy (void) {
//  gtk_main_quit ();
}

int exit_code = 0;
int argc2;
char **argv2;
osci::managerWindow *pwindow;
// Shared  throught socket GTK window object.
/**
 * Gtk application thread.
 */
void threadrun1 () {
  std::cout << "create new thread..." << std::endl;
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc2, argv2,
      "org.gtkmm.examples.base");

  osci::managerWindow *window = new osci::managerWindow();
  pwindow = window;
  window->set_default_size(200, 200);

  exit_code = app->run(*window);
  delete window;
}

/**
 * Tcp server thread to async sokect listening.
 */
void threadrun2 () {
  std::cout << "create new thread..." << std::endl;
  try {
    boost::asio::io_service io_service;
    osci::tcp_server server(io_service);
    io_service.run();
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

int main (int argc, char *argv[]) {
  ::argc2 = argc;
  ::argv2 = argv;
  boost::thread thread1(threadrun1);
  boost::thread thread2(threadrun2);
  thread1.join();
  thread2.join();

  return exit_code;
}
