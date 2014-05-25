/*
** channel.c for myirc in /home/kersal_e/Dropbox/myirc/irc_tmp/src_server
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Tue Apr 29 20:45:23 2014 Elliot Kersale
** Last update Tue Apr 29 21:41:21 2014 Elliot Kersale
*/

#include		"serveur.h"

int			set_channel(t_user *list, t_user *tmp, char *chan, char *null)
{
  (void)null;
  while (list && list->socket != tmp->socket)
    list = list->next;
  if (!list)
    {
      write_msg(ERROR_OCC, tmp->socket);
      return (EXIT_SUCCESS);
    }
  if (list->chan && *list->chan)
    free(list->chan);
  if (!chan || !*chan)
    {
      list->chan = "\0";
      write_msg(CHAN_LEFT, tmp->socket);
    }
  else
    {
      list->chan = format_name(chan);
      write_msg(CHAN_JOIN, tmp->socket);
    }
  return (EXIT_SUCCESS);
}

int			show_channel(t_user *list, t_user *tmp, char *chan, char *null)
{
  char			*msg;

  (void)chan;
  (void)null;
  if ((msg = malloc((3 * 4096) * sizeof(char))) == NULL)
    return (EXIT_SUCCESS);
  sprintf(msg, CHAN_AV);
  while (list != NULL)
    {
      sprintf(msg, "%s- %s\n", msg, list->chan);
      list = list->next;
    }
  write_msg(msg, tmp->socket);
  return (EXIT_SUCCESS);
}
