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
      //Signal handlers:
      void on_button_sql();
      void startTcpServer();
      void on_button_server();
      void on_button_notify();
      void on_notebook_switch_page(Gtk::Widget* page, guint page_num);

      static int sqlResult(void *NotUsed, int argc, char **argv, char **azColName);
      // Database object.
      sqlite3 *db;
      int dbrc;
      char *zErrMsg;

  };
#endif //GTKMM_WINDOW_H
