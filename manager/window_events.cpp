/**
 * @file
 * Provides manager window events handlers.
 */

#include "window.hpp"
#include <iostream>
#include <libnotify/notify.h>

/**
 * Event handler definition.
 */
void osci::managerWindow::on_button_notify() {
  notify_init("Initialization");
	NotifyNotification *notification = notify_notification_new(
    "Osci notification:",
    "Hello,\n This is an example notification.",
    "dialog-information"
  );

	notify_notification_show(notification, NULL);
}

/**
 * Event handler definition.
 */
void osci::managerWindow::on_button_server() {
  // @todo change button.
}

/**
 * Event handler definition.
 */
void osci::managerWindow::on_button_sql() {
  zErrMsg = 0;

  if (dbrc) {
    std::cout << "Can't open database: " << sqlite3_errmsg(db) << "\n";
    sqlite3_close(db);
  }

  dbrc = sqlite3_exec(db, "SELECT * FROM a;", sqlFetch, 0, &zErrMsg);

}

/**
 * Event handler defenition.
 */
void osci::managerWindow::on_notebook_switch_page(Gtk::Widget* page, guint page_num) {
  std::cout << "Switched to tab with index " << page_num << std::endl;
}
