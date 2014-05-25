/*
** ncurses.c for  in /home/kersal_e/Dropbox/myirc/PSU_2013_myirc/debug/ncurses
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Apr 28 16:36:16 2014 Elliot Kersale
** Last update Sun May 25 02:13:25 2014 Elliot Kersale
*/

#include		"client.h"

int			get_win_size(int *x, int *y)
{
  struct winsize	win;

  if (ioctl(0, TIOCGWINSZ, &win) < 0)
    return (EXIT_FAILURE);
  ioctl(0, TIOCGWINSZ, &win);
  *x = win.ws_col;
  *y = win.ws_row;
  return (EXIT_SUCCESS);
}

int			count_lines(t_txt *txt)
{
  int			i;

  i = 0;
  while (txt)
    {
      i += 1 + strlen(txt->buff) / (COLS - 2);
      txt = txt->next;
    }
  return (i);
}

void			txt_to_win(WINDOW *win, t_txt **txt)
{
  t_txt			*tmp;

  wclear(win);
  wmove(win, 0, 0);
  while (count_lines(*txt) > LINES - 6)
    {
      if (strlen((*txt)->buff) > (unsigned)(COLS - 2))
  	sprintf((*txt)->buff, "%s", (*txt)->buff + COLS - 3);
      else
  	remove_txt(txt);
    }
  if (!*txt)
    return ;
  tmp = *txt;
  while (tmp)
    {
      wprintw(win, "%s\n", tmp->buff);
      tmp = tmp->next;
    }
  wrefresh(win);
}

void			refresh_all(t_lib *lib)
{
  wrefresh(lib->wb1);
  wrefresh(lib->wb2);
  wrefresh(lib->wmsg);
  wrefresh(lib->win);
}

int			close_ncurses(t_lib *lib)
{
  delwin(lib->wmsg);
  delwin(lib->wb1);
  delwin(lib->win);
  delwin(lib->wb2);
  endwin();
  return (0);
}
