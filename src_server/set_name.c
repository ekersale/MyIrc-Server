/*
** set_name.c for my_irc in /home/kersal_e/Dropbox/myirc/irc_tmp/src_server
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Tue Apr 29 20:48:13 2014 Elliot Kersale
** Last update Tue Apr 29 21:35:32 2014 Elliot Kersale
*/

#include		"serveur.h"

void			put_name_list(t_user *list, char *name)
{
  if (list->name)
    free(list->name);
  if (strlen(name) == 1 && name[0] == '\n')
    list->name = NULL;
  else
    list->name = format_name(name);
  return ;
}

int			set_name(t_user *list, t_user *tmp, char *name, char *null)
{
  char			*buff;

  (void)null;
  if (name == NULL)
    {
      write_msg(ERR_SET_NAME, tmp->socket);
      return (EXIT_FAILURE);
    }
  if ((buff = malloc((strlen(name) + 100) * sizeof(char))) == NULL)
    return (EXIT_SUCCESS);
  while (list && list->socket != tmp->socket)
    list = list->next;
  if (!list)
    {
      write_msg(ERROR_OCC, tmp->socket);
      return (EXIT_SUCCESS);
    }
  put_name_list(list, name);
  sprintf(buff, NOW_KNOWN, list->name);
  write_msg(buff, tmp->socket);
  return (EXIT_SUCCESS);
}

