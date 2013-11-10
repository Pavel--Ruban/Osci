/**
 * @file
 * Provides manager GTK window.
 */

#include "window.hpp"
#include <iostream>
#include <stdio.h>
#include "../server/asyncServer.hpp"
#include <libnotify/notify.h>

/**
 * Destructor definition.
 */
osci::managerWindow::~managerWindow() { }

/**
 * SQL result callback.
 */
int osci::managerWindow::sqlResult(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;
  for(i = 0; i < argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

/**
 * Constructor definition.
 */
osci::managerWindow::managerWindow() :
  // Construct init.m_VBox
  m_VBox(Gtk::ORIENTATION_HORIZONTAL),
  m_Label1("Configuration"),
  m_Label2("About"),
  m_Button_SQL("SQL"),
  m_Button_Server("Start Server"),
  m_Button_Notify("Notify")
  // Open connection to database.
  {

  /* Set some window properties */
  set_title("Osci, created by Pavel Ruban");
  set_size_request(300, 300);

  /* Sets the border width of the window. */
  set_border_width(1);


//  Glib::RefPtr<Gdk::Screen> screen = this->get_screen();

  add(m_VBox);
  //Add the Notebook, with the button underneath:
  m_Notebook.set_border_width(10);
  m_VBox.pack_start(m_Notebook);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_SQL, Gtk::PACK_SHRINK);
  m_Button_SQL.signal_clicked().connect(sigc::mem_fun(*this,
              &osci::managerWindow::on_button_sql) );

  m_ButtonBox.pack_start(m_Button_Server, Gtk::PACK_SHRINK);
  m_Button_Server.signal_clicked().connect(sigc::mem_fun(*this,
              &osci::managerWindow::on_button_server) );

  m_ButtonBox.pack_start(m_Button_Notify, Gtk::PACK_SHRINK);
  m_Button_Notify.signal_clicked().connect(sigc::mem_fun(*this,
              &osci::managerWindow::on_button_notify) );


  //Add the Notebook pages:
  m_Notebook.append_page(m_Label1, "This page attemps to connect to server via tcp protocol");
  m_Notebook.append_page(m_Label2, "Under construction");

  m_Notebook.signal_switch_page().connect(sigc::mem_fun(*this,
              &managerWindow::on_notebook_switch_page) );

  show_all_children();
}

/**
 * Event handler definition.
 */
void osci::managerWindow::on_button_notify() {
  notify_init("Hello world!");
	NotifyNotification *Hello = notify_notification_new("Hello world", "This is an example notification.", "dialog-information");
	notify_notification_show(Hello, NULL);
}

void run() {
  try {
    boost::asio::io_service io_service;
    osci::tcp_server server(io_service);
    io_service.run();
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

/**
 * Event handler definition.
 */
void osci::managerWindow::on_button_server() {

}

/**
 * Event handler definition.
 */
void osci::managerWindow::on_button_sql() {
  dbrc = sqlite3_open("osci.db", &db);
  zErrMsg = 0;

  if (dbrc) {
    std::cout << "Can't open database: " << sqlite3_errmsg(db) << "\n";
    sqlite3_close(db);
  }

  dbrc = sqlite3_exec(db, "SELECT * FROM a;", sqlResult, 0, &zErrMsg);

}

/**
 * Event handler defenition.
 */
void osci::managerWindow::on_notebook_switch_page(Gtk::Widget* page, guint page_num) {
  std::cout << "Switched to tab with index " << page_num << std::endl;
}
