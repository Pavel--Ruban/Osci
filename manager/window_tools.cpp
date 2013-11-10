/**
 * @file
 * Provides manager services callbacks.
 */

#include "window.hpp"
#include <stdio.h>

/**
 * SQL fetch result callback.
 */
int osci::managerWindow::sqlFetch(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;
  for(i = 0; i < argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

