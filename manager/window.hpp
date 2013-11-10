/**
 * @file
 * Manager application interface.
 *
 * The goal of programm is to help manager to help
 * and track programmers work (estimates, %done, spent time)
 * Notification if something goes wrong.
 *
 * @author Pavel Ruban
 * @contact http://pavelruban.org
 * @mail pavelruban@mail.com
 * @github https://github.com/Pavel--Ruban
 */

#ifndef GTKMM_WINDOW_H

  #define GTKMM_WINDOW_H

  #include <gtkmm.h>
  #include <sqlite3.h>
  #include <gtkmm/application.h>

  namespace osci {
    class managerWindow;
  }

  class osci::managerWindow : public Gtk::Window {
    public:
      managerWindow();
      virtual ~managerWindow();

      //Child widgets:
      Gtk::Box m_VBox;
      Gtk::Notebook m_Notebook;

      Gtk::Label m_Label1, m_Label2;

      Gtk::ButtonBox m_ButtonBox;

      Gtk::Button m_Button_SQL;
      Gtk::Button m_Button_Server;
      Gtk::Button m_Button_Notify;

    protected:
      // Signal handlers:
      // Buttons.
      void on_button_sql();
      void on_button_server();
      void on_button_notify();

      // Tabs.
      void on_notebook_switch_page(Gtk::Widget* page, guint page_num);

      // Handler to fetch SQL queries data.
      static int sqlFetch(void *NotUsed, int argc, char **argv, char **azColName);

      // Database object.
      sqlite3 *db;
      int dbrc;
      char *zErrMsg;

  };

#endif //GTKMM_WINDOW_H
