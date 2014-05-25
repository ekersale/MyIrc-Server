/*
** select.c for my_irc in /home/kersal_e/Dropbox/myirc/irc_tmp/src_server
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Tue Apr 29 20:51:19 2014 Elliot Kersale
** Last update Tue Apr 29 22:37:37 2014 Julien Thompson
*/

#include		"serveur.h"

void			reset_list(fd_set *rfds, t_user *usr, t_serv *serv, int max)
{
  FD_ZERO(rfds);
  FD_SET(serv->s, rfds);
  while (usr)
    {
      FD_SET(usr->socket, rfds);
      usr = usr->next;
    }
  if (select(max + 1, rfds, NULL, NULL, NULL) == -1)
    {
      perror("select()");
      return ;
    }
}

void			close_client(t_user *tmp, t_user **list)
{
  char			*buff;

  if ((buff = malloc(4096 * sizeof(char))) == NULL)
    return ;
  close(tmp->socket);
  sprintf(buff, DECO_CLI, tmp->name);
  send_msg(*list, tmp, buff, 2);
  remove_user(list, tmp->name);
  return ;
}

void			client_connexion(int *max, int socks, fd_set *readfd)
{
  printf(CO_CLI);
  if (socks > *max)
    *max = socks;
  FD_SET(socks, readfd);
}

void			accept_connect(int *socks, t_serv *serv)
{
  if ((*socks = accept(serv->s, (struct sockaddr *)&(serv->sin_client),
		      (socklen_t *)&(serv->client_len))) == -1)
    perror("accept()");
}

int			run_serveur(t_serv *serv)
{
  t_user		*user_list;
  fd_set		readfd;
  int			max;
  int			socks;
  char			*buff;

  max = serv->s;
  user_list = NULL;
  if ((buff = malloc(4096 * sizeof(char))) == NULL)
    return (EXIT_FAILURE);
  while (1)
    {
      reset_list(&readfd, user_list, serv, max);
      if (FD_ISSET(serv->s, &readfd))
	{
	  accept_connect(&socks, serv);
	  if (read_client(socks, buff) != 0)
	    {
	      client_connexion(&max, socks, &readfd);
	      add_user(&user_list, DEFAULT_USER, socks, NULL);
	    }
	}
      else
	send_rcv(&user_list, &readfd);
    }
}
