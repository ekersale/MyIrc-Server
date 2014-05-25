/*
** send_msg.c for myirc in /home/kersal_e/Dropbox/myirc/irc_tmp/src_server
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Tue Apr 29 20:28:35 2014 Elliot Kersale
** Last update Tue Apr 29 21:41:08 2014 Elliot Kersale
*/

#include		"serveur.h"

void			who_s_send(t_user *list, char *buff, t_user *tmp, int check)
{
  char			*msg;

  if ((msg = malloc((strlen(buff) + strlen(tmp->name) + 10)
		    * sizeof(char))) == NULL)
    return ;
  if (check == 0)
    {
      sprintf(msg, "%s : %s", tmp->name ,buff);
      write_msg(msg, list->socket);
    }
  if (check == 1)
    {
      sprintf(msg, "%s", buff);
      write_msg(msg, list->socket);
    }
}

int			send_msg(t_user *list, t_user *tmp, char *buff, int check)
{
  char			*msg;

  if ((msg = malloc((strlen(buff) + strlen(tmp->name) + 10)
		    * sizeof(char))) == NULL)
    return (EXIT_FAILURE);
  while (list != NULL)
    {
      if (strcmp(list->chan, tmp->chan) == 0 && list->chan != NULL)
	{
	  who_s_send(list, buff, tmp, check);
	  if (check == 2)
	    if (list->socket != tmp->socket)
	      {
		sprintf(msg, "%s", buff);
		write_msg(msg, list->socket);
	      }
	}
      list = list->next;
    }
  return (0);
}

int			send_spe_msg(t_user *list, t_user *tmp, char *msg, char *user)
{
  char			*fin_msg_to;
  char			*fin_msg_from;

  if (!msg)
    return (EXIT_SUCCESS);
  if ((fin_msg_to = malloc((strlen(format_name(user)) + strlen(msg) + 10)
			   * sizeof(char))) == NULL)
    return (EXIT_SUCCESS);
  if ((fin_msg_from = malloc((strlen(tmp->name) + strlen(msg) + 10)
			     * sizeof(char))) == NULL)
    return (EXIT_SUCCESS);
  sprintf(fin_msg_to, "de %s : %s\n", tmp->name, msg);
  sprintf(fin_msg_from, "à %s : %s\n", format_name(user), msg);
  while (list != NULL)
    {
      if (strcmp(list->name, format_name(user)) == 0 && list->socket != tmp->socket)
	{
	  write_msg(fin_msg_to, list->socket);
	  write_msg(fin_msg_from, tmp->socket);
	  return (EXIT_SUCCESS);
	}
      list = list->next;
    }
  write_msg(USER_NF, tmp->socket);
  return (EXIT_SUCCESS);
}

