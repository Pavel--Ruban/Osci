#include <libnotifymm.h>
int main(int argc, char *argv[]) {
	Notify::init("Hello world!");
	Notify::Notification Hello("Hello world", "This is an example notification.", "dialog-information");
  Hello.show();
}
