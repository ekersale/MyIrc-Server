/*
** input_ncurses.c for irc in /home/kersal_e/Downloads/irc_tmp/src_client
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Tue Apr 29 19:36:47 2014 Elliot Kersale
** Last update Tue Apr 29 22:39:36 2014 Julien Thompson
*/

#include		"client.h"

char                    *get_input(t_lib *lib)
{
  int                   c;
  int                   i;
  char                  buff[4096];

  bzero(buff, 4096);
  i = 0;
  while ((c = wgetch(lib->win)) != '\n')
    {
      if (c == 127)
        {
          i--;
          if (i < 0)
            i = 0;
          else
            buff[i] = 0;
        }
      else
        buff[i++] = (char)c;
      mvwprintw(lib->win, 0, 0, "%s ", buff);
      /* wrefresh(lib->win); */
      refresh_all(lib);
    }
  wclear(lib->win);
  /* wrefresh(lib->win); */
  refresh_all(lib);
  return (strdup(buff));
}

void                    treat_input(t_lib *lib, char *buff)
{
  int                   max;

  if (strncmp(buff, SERVER, 7) == 0)
    connect_server(lib, buff, &max);
  else
    if (strncmp(buff, EXIT, 5) == 0)
      {
        close_ncurses(lib);
        exit(1);
      }
    else
      if (lib->s != -1)
        {
          if (send(lib->s, buff, strlen(buff), 0) == -1)
            add_txt(&lib->msg, ERROR_SEND);
        }
      else
        add_txt(&lib->msg, CO_SERVER);
}

void                    *routine_getinput(t_lib *lib)
{
  char                  *buff;

  lib->s = -1;
  while (1)
    {
      refresh_all(lib);
      txt_to_win(lib->wmsg, &lib->msg);
      buff = get_input(lib);
      treat_input(lib, buff);
      txt_to_win(lib->wmsg, &lib->msg);
      free(buff);
    }
}
