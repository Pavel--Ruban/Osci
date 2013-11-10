#include "../server/asyncServer.hpp"
#include "window.hpp"
#include <boost/thread.hpp>

void destroy (void) {
  gtk_main_quit ();
}

// Global scope is shared between threads.
int status = 0;

// Share input arguments.
int argc;
char **argv;

// Allow thread to change manager application state.
osci::managerWindow *pwindow;

/**
 * Gtk application thread.
 */
void thread_run_1 () {
  std::cout << "create new thread..." << std::endl;
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  // Allocate in heap memory window object to share it.
  osci::managerWindow *window = new osci::managerWindow();

  // Store window pointer within global scope.
  pwindow = window;
  window->set_default_size(200, 200);

  status = app->run(*window);

  // Free memory.
  delete window;
}

/**
 * Tcp server thread to async socket listening.
 */
void thread_run_2 () {
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
  // Share input arguments.
  ::argc = argc;
  ::argv = argv;

  // Split program into two separate threads.
  boost::thread thread1(thread_run_1);
  boost::thread thread2(thread_run_2);
  thread1.join();
  thread2.join();

  return status;
}
