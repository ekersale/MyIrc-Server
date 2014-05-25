/*
** main.c for myirc in /home/kersal_e/Dropbox/myirc/PSU_2013_myirc/includes
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Tue Apr 29 18:11:44 2014 Elliot Kersale
** Last update Tue Apr 29 18:53:22 2014 Elliot Kersale
*/

#include		"client.h"

int			main()
{
  t_lib			lib;
  pthread_t		com;

  lib.msg = NULL;
  init_mutex(&lib.mutex);
  init_ncurses(&lib);
  com = init_thread(&lib, &do_actions);
  routine_getinput(&lib);
  join_thread(&com);
  close(lib.s);
  close_ncurses(&lib);
  return (1);
}
