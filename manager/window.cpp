/**
 * @file
 * Provides manager GTK window.
 */

#include "window.hpp"
#include <iostream>
#include <stdio.h>

/**
 * Destructor declaration.
 */
osci::managerWindow::~managerWindow() { }

/**
 * Constructor declaration.
 */
osci::managerWindow::managerWindow()
  : m_VBox(Gtk::ORIENTATION_HORIZONTAL),
  m_Label1("Configuration"),
  m_Label2("About"),
  m_Button_SQL("SQL"),
  m_Button_Server("Start Server"),
  m_Button_Notify("Notify") {

  // Open database connection.
  dbrc = sqlite3_open("osci.db", &db);

  // Set some window properties.
  set_title("Osci, created by Pavel Ruban");
  set_size_request(300, 300);

  // Sets the border width of the window.
  set_border_width(1);

  add(m_VBox);

  //Add the Notebook, with the button underneath.
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
