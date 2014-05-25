/*
** commands.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp/client_src
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 15:08:35 2014 Elliot Kersale
** Last update Tue Apr 29 22:49:32 2014 Julien Thompson
*/

#include		"client.h"

int			my_malloc(char **str)
{
  if ((*str = malloc(4096 * sizeof(char))) == NULL)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

void			fdisset(t_lib *lib, char *str, fd_set *rfd)
{
  if (FD_ISSET(lib->s, rfd))
    {
      memset(str, 0, 4096);
      if (recv(lib->s, str, 4096, 0) == -1)
	error("recv()");
      else
	{
	  if (strlen(str) > 0)
	    {
	      add_txt(&lib->msg, str);
	      txt_to_win(lib->wmsg, &lib->msg);
	      /* wrefresh(lib->wmsg); */
	      refresh_all(lib);
	    }
	}
    }
}

int			init_ncurses(t_lib *lib)
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  lib->wmsg = newwin(LINES - 6, COLS - 3, 1, 2);
  lib->win = newwin(2, COLS - 3, LINES - 3, 2);
  lib->wb1 = newwin(LINES - 4, COLS, 0, 0);
  lib->wb2 = newwin(4, COLS, LINES - 4, 0);
  idlok(lib->wmsg, TRUE);
  scrollok(lib->wmsg, TRUE);
  idlok(lib->win, TRUE);
  scrollok(lib->win, TRUE);
  box(lib->wb1, '|', '-');
  box(lib->wb2, '|', '-');
  /* wnoutrefresh(lib->wb1); */
  /* wnoutrefresh(lib->wb2); */
  /* wnoutrefresh(lib->wmsg); */
  /* wnoutrefresh(lib->win); */
  refresh_all(lib);
  curs_set(0);
  return (0);
}

void			*do_actions(void *args)
{
  fd_set		rfd;
  t_lib			*lib;
  char			*str;

  lib = (t_lib *)args;
  if (my_malloc(&str) == EXIT_FAILURE)
    return (NULL);
  while (1)
    {
      FD_ZERO(&rfd);
      if (lib->s != -1)
	{
	  FD_SET(lib->s, &rfd);
	  if (select(lib->s + 1, &rfd, NULL, NULL, NULL) == -1)
	    error("select()");
	  fdisset(lib, str, &rfd);
	}
    }
  return (NULL);
}
