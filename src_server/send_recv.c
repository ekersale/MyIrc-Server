/*
** send_recv.c for myirc in /home/kersal_e/Dropbox/myirc/irc_tmp/src_server
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Tue Apr 29 21:07:44 2014 Elliot Kersale
** Last update Tue Apr 29 21:39:03 2014 Elliot Kersale
*/

#include		"serveur.h"

int			send_rcv(t_user **list, fd_set *rdfs)
{
  t_user		*tmp;
  char			*buff;

  if (!list)
    return (EXIT_SUCCESS);
  tmp = *list;
  if ((buff = malloc(4096 * sizeof(char))) == NULL)
    return (-1);
  while (tmp != NULL)
    {
      if (FD_ISSET(tmp->socket, rdfs))
	{
	  memset(buff, 0, 4096);
	  if (read_client(tmp->socket, buff) == 0)
	    close_client(tmp, list);
	  else
	    if (check_cmd(buff, *list, tmp) == EXIT_FAILURE)
	      send_msg(*list, tmp, buff, 0);
	}
      tmp = tmp->next;
    }
  return (0);
}
