/*
** gtk_func.c for gtk_func in /home/kersale/Dropbox/myirc/PSU_2013_myirc/src_client
** 
** Made by Elliot Kersale
** Login   <kersale@ubuntu>
** 
** Started on  Wed Apr 16 18:25:49 2014 Elliot Kersale
** Last update Sun Apr 20 19:44:23 2014 Julien Thompson
*/

#include		"my_irc.h"

void			text_toggle_editable(GtkWidget *checkbutton,
					     GtkWidget *text)
{
  gtk_text_set_editable(GTK_TEXT(text),
                        GTK_TOGGLE_BUTTON(checkbutton)->active);
}

void			text_toggle_word_wrap(GtkWidget *checkbutton,
					      GtkWidget *text)
{
  gtk_text_set_word_wrap(GTK_TEXT(text),
                         GTK_TOGGLE_BUTTON(checkbutton)->active);
}

void			close_application(GtkWidget *widget,
					  gpointer data)
{
  (void)widget;
  (void)data;
  gtk_main_quit();
  //  exit(-1);
}
