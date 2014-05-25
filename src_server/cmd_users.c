/*
** cmd_users.c for myirc in /home/kersal_e/Dropbox/myirc/irc_tmp/src_server
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Tue Apr 29 20:40:39 2014 Elliot Kersale
** Last update Tue Apr 29 21:21:36 2014 Elliot Kersale
*/

#include		"serveur.h"

void			void_value(char *str1, char *str2)
{
  (void)str1;
  (void)str2;
}

int			show_users(t_user *list, t_user *tmp, char *tmp2, char *tmp3)
{
  t_user		*tmp_list;
  char			*msg;
  int			count;

  void_value(tmp2, tmp3);
  tmp_list = list;
  count = 0;
  while (tmp_list != NULL)
    {
      if (strcmp(tmp_list->chan, tmp->chan) == 0)
	count += strlen(tmp_list->name);
      tmp_list = tmp_list->next;
    }
  if ((msg = malloc((count + 200 + strlen(tmp->chan)) * sizeof(char))) == NULL)
    return (EXIT_SUCCESS);
  sprintf(msg, CHAN_CO, tmp->chan);
  while (list != NULL)
    {
      if (strcmp(list->chan, tmp->chan) == 0)
	sprintf(msg, "%s- %s\n", msg, list->name);
      list = list->next;
    }
  write_msg(msg, tmp->socket);
  free(tmp_list);
  return (EXIT_SUCCESS);
}
