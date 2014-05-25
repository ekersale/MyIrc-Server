/*
** txt.c for  in /home/kersal_e/Dropbox/myirc/PSU_2013_myirc/debug/ncurses
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Apr 28 18:39:51 2014 Elliot Kersale
** Last update Sun May 25 02:14:21 2014 Elliot Kersale
*/

#include	"client.h"

int		add_txt(t_txt **list, char *buff)
{
  t_txt		*new;
  t_txt		*temp;

  if (!(new = malloc(sizeof(t_txt))))
    return (-1);
  snprintf(new->buff, 4096, "%s", buff);
  if (new->buff[strlen(buff) - 1] == '\n')
    new->buff[strlen(buff) - 1] = 0;
  new->next = NULL;
  if (!*list)
      *list = new;
  else
    {
      temp = *list;
      while (temp->next)
	temp = temp->next;
      temp->next = new;
    }
  return (0);
}

int		remove_txt(t_txt **list)
{
  t_txt		*ptr;
  t_txt		*tmp;

  ptr = *list;
  tmp = NULL;
  if (!ptr)
    return (-1);
  if (!tmp)
    *list = ptr->next;
  else
    tmp->next = ptr->next;
  free(ptr);
  return (0);
}
