#include "cs32.h"

/*This is the mian c file of the program! 1090310____ */

/*
 * function: the main form for the task manager
 * parameter:
 * return 0 if successful
 * 2012 5 15
 */

int main (int argc, char *argv[])
{

  GtkWidget *MainWindow;
  gtk_set_locale ();
  gtk_init(&argc, &argv);
  /*create the main window*/
  MainWindow = create_main_window();
  gtk_widget_show(MainWindow);
   
  /*This is a loop*/
  gtk_main ();
  return 0;
}
