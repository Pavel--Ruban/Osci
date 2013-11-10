#include "window.hpp"
#include "client.hpp"
#include <iostream>

/**
 * Destructor definition.
 */
clientWindow::~clientWindow() { }

/**
 * Constructor definition.
 */
clientWindow::clientWindow() :
  // Construct init.m_VBox
  m_VBox(Gtk::ORIENTATION_HORIZONTAL),
  m_Label1("Configuration"),
  m_Label2("About"),
  m_Button_Quit("Connect")

  {

  /* Set some window properties */
  set_title("Pavel Ruban notify client servet application for I20");
  set_size_request(300, 300);

  /* Sets the border width of the window. */
  set_border_width(1);


//  Glib::RefPtr<Gdk::Screen> screen = this->get_screen();

  add(m_VBox);
  //Add the Notebook, with the button underneath:
  m_Notebook.set_border_width(10);
  m_VBox.pack_start(m_Notebook);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
              &clientWindow::on_button_quit) );

  //Add the Notebook pages:
  m_Notebook.append_page(m_Label1, "This page attemps to connect to server via tcp protocol");
  m_Notebook.append_page(m_Label2, "Under construction");

  m_Notebook.signal_switch_page().connect(sigc::mem_fun(*this,
              &clientWindow::on_notebook_switch_page) );

  show_all_children();
}

/**
 * Event handler defenition.
 */
void clientWindow::on_button_quit() {
//  hide();
    g_print ("Connecting...\n");
    client c;
    c.host = "127.0.0.1";
    c.port = "5556";
    c.connect();
    char *response;

    response = c.send("i20-notify 1.0");
    std::cout << response << std::endl;
}

/**
 * Event handler defenition.
 */
void clientWindow::on_notebook_switch_page(Gtk::Widget* page, guint page_num) {
  std::cout << "Switched to tab with index " << page_num << std::endl;

  //You can also use m_Notebook.get_current_page() to get this index.
}
