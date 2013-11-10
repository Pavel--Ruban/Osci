#include "client.hpp"
#include "window.hpp"

void destroy (void) {
//  gtk_main_quit ();
}

int main (int argc, char *argv[]) {
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  clientWindow window;
  Gtk::Box m_VBox;
  Gtk::Notebook m_Notebook;
  Gtk::Label m_Label1, m_Label2;
  Gtk::ButtonBox m_ButtonBox;
  Gtk::Button m_Button_Quit;

  window.set_default_size(200, 200);


  return app->run(window);
}
