/*
** user.c for my_irc in /home/kersale/Dropbox/myirc/PSU_2013_myirc/src_server
** 
** Made by Elliot Kersale
** Login   <kersale@epitech.net>
** 
** Started on  Thu Apr 17 18:28:57 2014 Elliot Kersale
** Last update Tue Apr 29 21:38:44 2014 Elliot Kersale
*/

#include	"serveur.h"

int		add_user(t_user **list, char *name, int socket, char *chan)
{
  t_user	*new;
  t_user	*temp;
  char		buff[4096];

  if (!(new = malloc(sizeof(t_user))) ||
      !(new->name = format_name(name)) || !(new->chan = format_name(chan)))
    return (-1);
  if (new->name[strlen(name) - 1] == '\n')
    new->name[strlen(name) - 1] = 0;
  new->socket = socket;
  new->next = NULL;
  sprintf(buff, NOW_KNOWN, new->name);
  write_msg(buff, new->socket);
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

int		remove_user(t_user **list, char *name)
{
  t_user	*ptr;
  t_user	*tmp;

  ptr = *list;
  tmp = NULL;
  while (ptr && strcmp(ptr->name, name))
    {
      tmp = ptr;
      ptr = ptr->next;
    }
  if (!ptr)
    return (-1);
  if (!tmp)
    *list = ptr->next;
  else
    tmp->next = ptr->next;
  free(ptr->name);
  if (ptr->chan && *ptr->chan)
    free(ptr->chan);
  free(ptr);
  return (0);
}
