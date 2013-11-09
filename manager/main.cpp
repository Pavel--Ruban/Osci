#include "client.hpp"
#include "window.hpp"

void destroy (void) {
//  gtk_main_quit ();
}

int main (int argc, char *argv[]) {
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  osci::managerWindow window;
  window.set_default_size(200, 200);

  return app->run(window);
}
